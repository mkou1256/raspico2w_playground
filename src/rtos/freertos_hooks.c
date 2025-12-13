/**
 * @file freertos_hooks.c
 * @brief FreeRTOS hook and callback functions implementation for Raspberry Pi Pico 2W
 * 
 * This file implements the required callback functions for FreeRTOS when using
 * static memory allocation (configSUPPORT_STATIC_ALLOCATION = 1).
 * 
 * These functions are mandatory when static allocation is enabled and provide
 * the memory buffers for FreeRTOS internal tasks.
 * 
 * NOTE: Do NOT create a separate header file for these functions.
 * The function declarations already exist in FreeRTOS's task.h
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* ========================================================================== */
/* Static Memory Allocation Callbacks (REQUIRED)                             */
/* ========================================================================== */

#if configSUPPORT_STATIC_ALLOCATION

/* Static memory buffers for Idle Task (Core 0) */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

/**
 * @brief Provides memory for the Idle task
 * 
 * This function is called by FreeRTOS during scheduler initialization to obtain
 * memory for the Idle task. The Idle task runs when no other tasks are ready.
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    configSTACK_DEPTH_TYPE *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = xIdleStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* Static memory buffers for Passive Idle Task (Core 1 on RP2350) */
/* This is only needed for multi-core configurations */
#if 1 

static StaticTask_t xPassiveIdleTaskTCBBuffer;
static StackType_t xPassiveIdleStack[configMINIMAL_STACK_SIZE];

/**
 * @brief Provides memory for the Passive Idle task (Pico 2 multi-core)
 * 
 * The RP2350 (Raspberry Pi Pico 2) has dual Cortex-M33 cores.
 * This function provides memory for the idle task on the second core.
 */
void vApplicationGetPassiveIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                           StackType_t **ppxIdleTaskStackBuffer,
                                           configSTACK_DEPTH_TYPE *pulIdleTaskStackSize,
                                           BaseType_t xPassiveIdleTaskIndex)
{
    *ppxIdleTaskTCBBuffer = &xPassiveIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = xPassiveIdleStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

#endif

#if configUSE_TIMERS

/* Static memory buffers for Timer Task */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

/**
 * @brief Provides memory for the Timer task
 * 
 * This function is called when software timers are enabled (configUSE_TIMERS = 1)
 * and static allocation is used. The Timer task manages software timers.
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     configSTACK_DEPTH_TYPE *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = xTimerStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

#endif /* configUSE_TIMERS */

#endif /* configSUPPORT_STATIC_ALLOCATION */

/* ========================================================================== */
/* Optional Hook Functions                                                   */
/* ========================================================================== */

#if configCHECK_FOR_STACK_OVERFLOW

/**
 * @brief Stack overflow detection hook
 * 
 * Called when FreeRTOS detects a stack overflow. This is a critical error
 * that indicates a task has used more stack space than allocated.
 * 
 * @param xTask Handle of the task that overflowed
 * @param pcTaskName Name of the task (null-terminated string)
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    /* Disable interrupts to prevent further damage */
    taskDISABLE_INTERRUPTS();
    
    /* Log the error (if printf is available) */
    printf("STACK OVERFLOW: Task '%s' (handle: %p)\n", pcTaskName, xTask);
    
    /* Infinite loop - system should be reset */
    for (;;) {
        /* You could toggle an LED here to indicate error */
        __asm volatile ("nop");
    }
}

#endif /* configCHECK_FOR_STACK_OVERFLOW */

#if configUSE_IDLE_HOOK

/**
 * @brief Idle task hook function
 * 
 * Called during each iteration of the Idle task. Useful for:
 * - Putting the CPU into low-power sleep mode
 * - Background garbage collection
 * - Feeding a watchdog timer
 * 
 * WARNING: This function must NOT attempt to block or suspend.
 */
void vApplicationIdleHook(void)
{
    /* Example: Could implement low-power mode here */
    /* __wfi(); */ /* Wait for interrupt - reduces power consumption */
}

#endif /* configUSE_IDLE_HOOK */

#if configUSE_TICK_HOOK

/**
 * @brief Tick interrupt hook function
 * 
 * Called from the tick interrupt at every tick (e.g., every 1ms if tick rate is 1000Hz).
 * Must be very short and fast - no blocking operations allowed.
 */
void vApplicationTickHook(void)
{
    /* Example: Could increment a counter for timing purposes */
    /* static uint32_t tick_count = 0;
       tick_count++; */
}

#endif /* configUSE_TICK_HOOK */

#if configUSE_MALLOC_FAILED_HOOK

/**
 * @brief Malloc failed hook function
 * 
 * Called when pvPortMalloc() fails to allocate memory.
 * This indicates the heap is exhausted or too fragmented.
 */
void vApplicationMallocFailedHook(void)
{
    /* Disable interrupts */
    taskDISABLE_INTERRUPTS();
    
    printf("MALLOC FAILED: FreeRTOS heap exhausted!\n");
    
    /* Infinite loop - system should be reset */
    for (;;) {
        __asm volatile ("nop");
    }
}

#endif /* configUSE_MALLOC_FAILED_HOOK */

/* ========================================================================== */
/* Debug/Utility Functions                                                   */
/* ========================================================================== */

/**
 * @brief Get current FreeRTOS heap usage statistics
 * 
 * Utility function to help debug memory issues.
 * Prints heap usage information if printf is available.
 */
void vPrintHeapStats(void)
{
    HeapStats_t heap_stats;
    vPortGetHeapStats(&heap_stats);
    
    printf("FreeRTOS Heap Statistics:\n");
    printf("  Available heap space:        %u bytes\n", heap_stats.xAvailableHeapSpaceInBytes);
    printf("  Largest free block:          %u bytes\n", heap_stats.xSizeOfLargestFreeBlockInBytes);
    printf("  Smallest free block:         %u bytes\n", heap_stats.xSizeOfSmallestFreeBlockInBytes);
    printf("  Number of free blocks:       %u\n", heap_stats.xNumberOfFreeBlocks);
    printf("  Minimum ever free bytes:     %u bytes\n", heap_stats.xMinimumEverFreeBytesRemaining);
    printf("  Successful allocations:      %u\n", heap_stats.xNumberOfSuccessfulAllocations);
    printf("  Successful frees:            %u\n", heap_stats.xNumberOfSuccessfulFrees);
}
