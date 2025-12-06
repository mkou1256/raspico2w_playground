cmake_minimum_required(VERSION 3.13)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SRC_DIR ${PROJECT_ROOT}/src)

# ---- SDK Import ----
include(pico_sdk_import.cmake)

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ---- Initialize SDK ----
pico_sdk_init()

# ---- Add executable ----
add_executable(blink 
    ${SRC_DIR}/blink.c
)

# ---- Link required libraries ----
# pico_stdlib = 普通のIO
# pico_cyw43_arch_none/WIFI = Pico W LED制御に必要
target_link_libraries(blink 
    pico_stdlib 
    pico_cyw43_arch_none
)

# ---- Enable USB or UART (optional) ----
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# ---- Create UF2 / binary output ----
pico_add_extra_outputs(blink)
