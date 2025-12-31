cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. IMPORTANT: Set the Port for Linux/GitHub Actions
set(FREERTOS_PORT GCC_POSIX CACHE STRING "")

# 2. Define the Config Target (Where FreeRTOSConfig.h lives)
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 3. Fetch FreeRTOS Kernel
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# 4. Create Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 5. Link Kernel + Config + System Threads
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    Threads::Threads
)