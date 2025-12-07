cmake_minimum_required(VERSION 3.13)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SRC_DIR ${PROJECT_ROOT}/src)

# ---- SDK Import ----
include(pico_sdk_import.cmake)

project(pico2w C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ---- Initialize SDK ----
pico_sdk_init()

# ---- Add executable ----
add_executable(pico2w 
    ${SRC_DIR}/system/main.c
    ${SRC_DIR}/app/dbg_print.c
    ${SRC_DIR}/control/usb_comm.c
    ${SRC_DIR}/utils/ring_buffer.c
)

# ---- Add include directories ----
target_include_directories(pico2w PRIVATE ${SRC_DIR}/include)

# ---- Link required libraries ----
# pico_stdlib = 普通のIO
# pico_cyw43_arch_none/WIFI = Pico W LED制御に必要
target_link_libraries(pico2w 
    pico_stdlib
    pico_cyw43_arch_none
)

# ---- Enable USB or UART (optional) ----
pico_enable_stdio_usb(pico2w 1)
pico_enable_stdio_uart(pico2w 0)

# ---- Create UF2 / binary output ----
pico_add_extra_outputs(pico2w)
