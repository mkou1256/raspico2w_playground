# pico-sdkを用いる際のCMakeList.txt構成
- [CMakeList.txt](../build/CMakeLists.txt)
```CMake
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
```

## 要素解説

- **cmake_minimum_required**
  - `cmake`の最低バージョンを指定する。
  - 指定バージョン以下の環境だと警告を出す。
- **set**
  - `${var}`として変数宣言できる。
  - CMakeList内で使用できる
- **include**
  - 他の`.cmake`ファイルを読み込む
  - `.cmake`に書かれたコマンドは即実行される（cのマクロと近いイメージ）
  - `.cmake`に書かれた関数は登録されるだけ（cの関数と同等）
  - pico_sdk_import.cmakeでは、
    - SDK全体をCMakeに追加している。`add_subdirectory`を実行している。
    - pico_sdk_initなどの固有のCMake関数を定義している。
- **pico_sdk_init**
  - ラズパイSDK特有のものなので割愛
- **add_executable**
  - コンパイル対象の実行ファイルとソースコードを登録する
  - `add_executable(target src)` --> srcをビルドしてtargetを生成する
- **target_link_libraries**
  - tartgetに必要なライブラリをリンクする
  - `target_link_libraries(blink pico_stdlib pico_cyw43_arch_none)` --> blink内で呼び出す命令に必要なライブラリをリンクしている
- **pico_enable_stdio_usb**
  - usb経由の`printf()`出力を有効化/無効化
  - 1 / 0
- **pico_enable_stdio_uart**
  -   uartでの`printf()`出力を有効化/無効化
  -   1 / 0
- **pico_add_extra_outputs**
  - ビルド成果物として、`.uf2`などを生成する