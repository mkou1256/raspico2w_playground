# CMakeLists.txtのメモ

- **add_executableにワイルドカード使えない**
  - その代わり、`file`でソースファイルをまとめた変数を作る
    ```cmake
    file(GLOB SYSTEM_SRC CONFIGURE_DEPENDS ${SRC_DIR}/system/*.c)
    ```
  - `CONFIGURE_DEPENDS`を付けるとCMakeがファイルを追跡してくれるらしい。
- **include pathを登録　--> `target_include_directories`**
- 