cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Setup Threads
find_package(Threads REQUIRED)

# 2. Setup FreeRTOS FetchContent
include(FetchContent)

# Fetch the Core Kernel
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)

# Fetch the POSIX Port (Crucial for Linux/CI)
FetchContent_Declare(
  freertos_posix
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel-Community-Supported-Ports.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(freertos_kernel freertos_posix)

# 3. Define the config target
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. Create Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 5. Add POSIX Port source and headers manually to bridge the gap
target_include_directories(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC
    ${freertos_kernel_SOURCE_DIR}/include
)

target_sources(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC/port.c
    ${freertos_posix_SOURCE_DIR}/POSIX/utils/wait_for_event.c
)

# 6. Link everything
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    ${CMAKE_THREAD_LIBS_INIT}
    rt  # Required for POSIX timers
)