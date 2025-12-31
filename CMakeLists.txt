cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Define the Config Target (Matches the Error Message solution)
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 2. Download FreeRTOS Kernel
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# 3. Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 4. Link everything
# We link the kernel and the posix port for simulation
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    Threads::Threads
)