cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Force the POSIX port for Linux/CI environment
set(FREERTOS_PORT GCC_POSIX CACHE STRING "" FORCE)

# 2. Find system thread support
find_package(Threads REQUIRED)

# 3. Define the configuration target for FreeRTOS
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. Fetch the FreeRTOS Kernel
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# 5. Create the executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 6. Link with the kernel, config, and POSIX threads
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    ${CMAKE_THREAD_LIBS_INIT}
)