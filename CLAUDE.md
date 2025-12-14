# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Raspberry Pi Pico 2 W (RP2350) embedded firmware project using FreeRTOS for multitasking. The project is currently in the RTOS integration phase, with USB communication and debug printing capabilities established.

**Target Board**: Pico 2 W (RP2350 platform)
**RTOS**: FreeRTOS (located in `libs/FreeRTOS-Kernel`)
**SDK**: Raspberry Pi Pico SDK (located in `libs/pico-sdk`)

## Build System

### Build Commands

Build the project:
```bash
cd build
./build.sh
```

The build script:
- Cleans the output directory (`build/out/`)
- Runs CMake with proper SDK paths and board configuration
- Creates a symlink to `compile_commands.json` in the project root
- Compiles using all available CPU cores

Build artifacts are located in `build/out/`, including:
- `pico2w.uf2` - Main firmware file for uploading to the board
- `pico2w.elf` - ELF binary for debugging
- `compile_commands.json` - For IDE integration

### CMake Configuration

The root CMakeLists.txt is located at `build/CMakeLists.txt`. Key configuration:
- `PICO_BOARD=pico2_w`
- `PICO_PLATFORM=rp2350`
- Source files are automatically globbed from `src/system/`, `src/app/`, `src/control/`, `src/utils/`
- USB stdio is enabled, UART stdio is disabled

## Code Architecture

### Directory Structure

```
src/
├── system/          # System initialization and main entry point
│   ├── system_init.c/h  - Hardware/peripheral initialization
│   └── system_entry.c   - main() and FreeRTOS task creation
├── app/             # Application-level functionality
│   ├── dbg_print.c/h    - Debug print with ANSI color and timestamps
│   └── task_test.c/h    - Test tasks for RTOS validation
├── control/         # Hardware control layers
│   ├── usb_comm.c/h     - USB communication with ring buffers
│   └── led.c            - LED control
├── utils/           # Utility modules
│   └── ring_buffer.c/h  - Thread-safe circular buffer
└── include/         # Shared headers
    ├── FreeRTOSConfig.h - FreeRTOS configuration
    ├── rtos_wrapper.h   - FreeRTOS abstraction macros
    └── typedef.h        - Common error codes and types
```

### Key Architectural Patterns

**Initialization Flow**:
1. `main()` in `system_entry.c`
2. Calls `systemInit()` which initializes in order:
   - stdio (USB)
   - CYW43 Wi-Fi chip (required for Pico W even if not using Wi-Fi)
   - USB communication + ring buffers
   - Debug print system
3. Creates FreeRTOS tasks
4. Starts FreeRTOS scheduler (never returns)

**Debug Print System** (`dbg_print.c`):
- Thread-safe via FreeRTOS mutex (`s_mtxDbgPrint`)
- Formatted output: `[LEVEL][timestamp] message`
- ANSI color-coded by log level (DEBUG/INFO/WARN/ERROR)
- Uses ring buffer for USB transmission
- Internal buffer size: 256 bytes

**USB Communication** (`usb_comm.c`):
- Separate TX/RX ring buffers (256 bytes each)
- `usbTx()`: Enqueues data and flushes immediately (synchronous)
- Ring buffers are mutex-protected for thread safety
- Uses `stdio_put_string()` for low-level USB transmission

**Ring Buffer** (`ring_buffer.c`):
- Circular buffer with head/tail pointers
- Thread-safe via FreeRTOS mutex
- Returns actual bytes enqueued/dequeued (may be partial if buffer is full/empty)
- Handles wrap-around using two memcpy operations when necessary

**RTOS Abstraction** (`rtos_wrapper.h`):
- Provides macros wrapping FreeRTOS APIs:
  - `mtx_handle_t` → `SemaphoreHandle_t`
  - `make_mtx()` → `xSemaphoreCreateMutex()`
  - `take_mtx(h)` → `xSemaphoreTake(h, portMAX_DELAY)`
  - `give_mtx(h)` → `xSemaphoreGive(h)`
- This abstraction layer allows potential RTOS portability

### Error Handling

All functions return standardized error codes defined in `typedef.h`:
- `E_SUCCESS` (0): Success
- `E_INIT` (-1): Initialization failure
- `E_TIMEOUT` (-2): Timeout
- `E_ARGUMENT` (-3): Invalid argument
- `E_BUFSIZE` (-4): Buffer size error
- `E_USBCOMM` (-5): USB communication error
- `E_OTHER` (-99): Other errors

Functions that return data length return positive values on success, negative error codes on failure.

### FreeRTOS Configuration

Key settings in `FreeRTOSConfig.h`:
- Tick rate: 1000 Hz (1ms resolution)
- Max priorities: 32 levels
- Minimal stack size: 512 words (2048 bytes)
- Heap: Heap4 allocation scheme
- Preemptive multitasking enabled

### Current Development Status

From `README.md`:
- ✅ LED control and GPIO
- ✅ USB communication established
- 🚧 RTOS integration (in progress):
  - Need to add mutex protection to debug print buffer (already done in code)
  - Need to create async send task with data-wait mechanism
- ⏳ Next: Command system with message receive task and command processing table
- ⏳ Future: Temperature/humidity sensor integration

## Important Notes

1. **Always include FreeRTOS headers** when writing new modules that use mutexes, tasks, or queues. Use the wrappers in `rtos_wrapper.h` for portability.

2. **Thread Safety**: Any shared resources must use mutex protection. See `ring_buffer.c` and `dbg_print.c` for examples.

3. **CYW43 Initialization**: The CYW43 chip must be initialized even if Wi-Fi/Bluetooth is not used, as it controls the onboard LED on Pico W.

4. **USB Communication**: The current implementation is synchronous. Plans include creating an async send task for better performance.

5. **CMake Source Globbing**: The build system uses `file(GLOB)` to automatically include all `.c` files in `src/system/`, `src/app/`, `src/control/`, and `src/utils/`. New source files in these directories are automatically included in the build.

6. **Stack Sizes**: When creating new FreeRTOS tasks, ensure adequate stack size. Current test tasks use 512 words (2048 bytes). Monitor stack usage with FreeRTOS stack overflow detection if needed.

7. **Japanese Comments**: The codebase contains Japanese comments. Maintain consistency by using Japanese for implementation details if that's the project's convention.
