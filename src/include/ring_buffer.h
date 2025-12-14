#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "typedef.h"
#include "rtos_wrapper.h" // for mtx

typedef struct ringBuffer {
    uint8_t* buffer;   // buffer pointer
    size_t bufferSize; // size of the buffer
    size_t head;       // head index of filled data
    size_t tail;       // tail index of filled data
    size_t count;      // number of filled data
    rtos_mutex_t mtx;  // mtx resource
} ringBuffer_t;

extern int8_t ringBufferInit(ringBuffer_t* rb, uint8_t* buffer, size_t bufferSize);
extern size_t ringBufferAvailableSize(ringBuffer_t* rb);
extern int32_t ringBufferEnqueue(ringBuffer_t* rb, const uint8_t* data, size_t len);
extern int32_t ringBufferDequeue(ringBuffer_t* rb, uint8_t* data, size_t len);

#endif // RING_BUFFER_H
