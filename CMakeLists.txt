cmake_minimum_required(VERSION 3.10)
project(rtos-cpp-controller)

set(CMAKE_CXX_STANDARD 17)

# 1. Setup Threads and define the POSIX port
find_package(Threads REQUIRED)
set(FREERTOS_PORT GCC_POSIX CACHE STRING "" FORCE)

# 2. Define the config library BEFORE fetching kernel
# Fixed: Added INTERFACE keyword to target_compile_definitions
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)

# 3. Fetch Core Kernel and POSIX Port extensions
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

# 4. Create the executable
add_executable(rtos_demo 
    src/main.cpp 
    src/Task.cpp
)

# 5. Add required include paths for POSIX simulation
target_include_directories(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC
    ${freertos_kernel_SOURCE_DIR}/include
)

# 6. Add specific POSIX port source files to the build
target_sources(rtos_demo PRIVATE 
    ${freertos_posix_SOURCE_DIR}/POSIX/GCC/port.c
    ${freertos_posix_SOURCE_DIR}/POSIX/utils/wait_for_event.c
)

# 7. Final linking
# 'rt' is the Real-time Extensions library required for POSIX timers
target_link_libraries(rtos_demo PRIVATE 
    freertos_kernel 
    freertos_config
    ${CMAKE_THREAD_LIBS_INIT}
    rt
)