cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. FIND THREADS FIRST
find_package(Threads REQUIRED)

# 2. Tell FreeRTOS to use the POSIX port
set(FREERTOS_PORT GCC_POSIX CACHE STRING "")

# 3. Define the Config Target
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. Fetch FreeRTOS Kernel
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel)

# 5. Create Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 6. Link everything
# Using ${CMAKE_THREAD_LIBS_INIT} is a safer way to link threads if Threads::Threads fails
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    Threads::Threads
    ${CMAKE_THREAD_LIBS_INIT}
)