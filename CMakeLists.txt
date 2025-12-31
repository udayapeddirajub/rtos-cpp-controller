cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Download FreeRTOS Kernel automatically
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# 2. Setup Include Directories
include_directories(include)

# 3. Create Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 4. Link FreeRTOS (POSIX port for Linux/GitHub Actions)
# Note: In a real embedded project, you'd link the ARM/ESP32 port here.
target_link_libraries(rtos_demo PRIVATE Threads::Threads)