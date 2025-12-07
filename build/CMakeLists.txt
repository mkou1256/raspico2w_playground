cmake_minimum_required(VERSION 3.13)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SRC_DIR ${PROJECT_ROOT}/src)

# ---- SDK Import ----
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)
project(pico2w C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ---- Initialize SDK ----
pico_sdk_init()

# ---- Add executable ----
file(GLOB SYSTEM_SRC CONFIGURE_DEPENDS ${SRC_DIR}/system/*.c)
file(GLOB APP_SRC CONFIGURE_DEPENDS ${SRC_DIR}/app/*.c)
file(GLOB CONTROL_SRC CONFIGURE_DEPENDS ${SRC_DIR}/control/*.c)
file(GLOB UTILS_SRC CONFIGURE_DEPENDS ${SRC_DIR}/utils/*.c)
add_executable(pico2w 
    ${SYSTEM_SRC}
    ${APP_SRC}
    ${CONTROL_SRC}
    ${UTILS_SRC}
)

# ---- Add include directories ----
target_include_directories(pico2w PRIVATE ${SRC_DIR}/include)

# ---- Link required libraries ----
target_link_libraries(pico2w 
    pico_stdlib
    pico_cyw43_arch_none
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

# ---- Enable USB or UART (optional) ----
pico_enable_stdio_usb(pico2w 1)
pico_enable_stdio_uart(pico2w 0)

# ---- Create UF2 / binary output ----
pico_add_extra_outputs(pico2w)
