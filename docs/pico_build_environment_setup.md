# Raspberry Pi Pico 2W + FreeRTOS ビルド環境構築手順書

## 概要

Ubuntu環境でRaspberry Pi Pico 2W向けのFreeRTOSベースのファームウェアをビルドするための最小限の環境構築手順です。

**対象OS**: Ubuntu 22.04 LTS (WSL含む)  
**ターゲット**: Raspberry Pi Pico 2W  
**RTOS**: FreeRTOS  
**ビルドシステム**: CMake + Pico SDK

---

## 1. システムの準備

### 1.1 システムアップデート

```bash
sudo apt update
sudo apt upgrade -y
```

### 1.2 ビルドツールのインストール

```bash
sudo apt install -y \
    build-essential \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    git \
    python3 \
    pkg-config \
    libusb-1.0-0-dev
```

---

## 2 プロジェクトをクローン

### 2.1 clone repository
```bash
# 作業ディレクトリに移動
cd ~/workspace

# GitHubからプロジェクトをクローン
git clone <your-project-repository-url>
cd <your-project-directory>
```

### 2.2 git submodule
```bash
# すべてのサブモジュールを初期化＆更新
git submodule update --init --recursive
```


## 3 ビルドの実行

```bash
cd build
./build.sh
```

成功すると build/out下に、`.uf2` ファイルなどが生成されます。

---
