cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Setup Threads and Posix Port setting
find_package(Threads REQUIRED)
set(FREERTOS_PORT GCC_POSIX CACHE STRING "" FORCE)

# 2. DEFINE CONFIG BEFORE FETCHING KERNEL (Fixes your error)
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(freertos_config PUBLIC projCOVERAGE_TEST=0)

# 3. Fetch Core and Community Ports
include(FetchContent)
FetchContent_Declare(
  freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)
FetchContent_Declare(
  freertos_posix
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel-Community-Supported-Ports.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(freertos_kernel freertos_posix)

# 4. Create Executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 5. Include Paths for the POSIX Port
target_include_directories(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC
    ${freertos_kernel_SOURCE_DIR}/include
)

# 6. Link Libraries (rt is for POSIX timers, required on Linux)
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    ${CMAKE_THREAD_LIBS_INIT}
    rt
)

# 7. Add the specific POSIX source files to the build
target_sources(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC/port.c
    ${freertos_posix_SOURCE_DIR}/POSIX/utils/wait_for_event.c
)