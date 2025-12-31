cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# Setup Threads and define the POSIX port BEFORE fetching kernel
find_package(Threads REQUIRED)
set(FREERTOS_PORT GCC_POSIX CACHE STRING "" FORCE)
set(FREERTOS_HEAP 4 CACHE STRING "" FORCE)

# Create config library BEFORE fetching kernel
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(freertos_config INTERFACE 
    projCOVERAGE_TEST=0
)

# Fetch FreeRTOS Kernel ONLY (POSIX port is included in kernel)
include(FetchContent)
FetchContent_Declare(
    freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# Create the executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# Link FreeRTOS kernel and config
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    Threads::Threads
    rt
)

# Includes for app sources
target_include_directories(rtos_demo PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${freertos_kernel_SOURCE_DIR}/include
)
