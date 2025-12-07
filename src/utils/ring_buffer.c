#include "ring_buffer.h"
#include "typedef.h"
#include "pico/stdlib.h"
#include <string.h>

int8_t ringBufferInit(ringBuffer_t* rb, uint8_t* buffer, size_t bufferSize)
{
    if (rb == NULL || buffer == NULL || bufferSize == 0) {
        return E_ARGUMENT;
    }
    rb->buffer = buffer;
    rb->bufferSize = bufferSize;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    return E_SUCCESS;
}

size_t ringBufferAvailableSize(ringBuffer_t* rb)
{
    if (rb == NULL) {
        return 0;
    }
    return rb->bufferSize - rb->count;
}

int32_t ringBufferEnqueue(ringBuffer_t* rb, const uint8_t* data, size_t len)
{
    if (rb == NULL || data == NULL || len == 0) {
        return E_ARGUMENT;
    }
    size_t bytesToEnqueue = (len < ringBufferAvailableSize(rb)) ? len : ringBufferAvailableSize(rb);
    
    if (bytesToEnqueue == 0) {
        return 0; // バッファがいっぱい
    }
    size_t bytesEnqueued = 0;

    // バッファの末尾まで書き込めるサイズを計算し、memcpyで書き込む
    size_t firstChunkRemaining = rb->bufferSize - rb->head;
    size_t firstChunkWriting = (bytesToEnqueue < firstChunkRemaining) ? bytesToEnqueue : firstChunkRemaining;
    memcpy(&rb->buffer[rb->head], data, firstChunkWriting);
    rb->head = (rb->head + firstChunkWriting) % rb->bufferSize;
    rb->count += firstChunkWriting;
    bytesToEnqueue -= firstChunkWriting;
    bytesEnqueued += firstChunkWriting;

    // 残りデータがなければ終了
    if (bytesToEnqueue == 0) {
        return bytesEnqueued;
    }
    
    // 残りのデータがある場合はBufferの先頭から書き込む
    memcpy(&rb->buffer[rb->head], &data[bytesEnqueued], bytesToEnqueue);
    rb->head = (rb->head + bytesToEnqueue) % rb->bufferSize;
    rb->count += bytesToEnqueue;
    bytesEnqueued += bytesToEnqueue;

    return bytesEnqueued;
}

int32_t ringBufferDequeue(ringBuffer_t* rb, uint8_t* data, size_t len)
{
    if (rb == NULL || data == NULL || len == 0) {
        return E_ARGUMENT;
    }
    size_t bytesToDequeue = (len < rb->count) ? len : rb->count;
    
    if (bytesToDequeue == 0) {
        return 0; // バッファが空
    }
    size_t bytesDequeued = 0;

    // tail --> head or tail --> buffer end まで読み込めるサイズを計算し、memcpyで読み込む
    size_t firstChunkEndIdx = (rb->head > rb->tail) ? rb->head : rb->bufferSize;
    size_t firstChunkRemaining = firstChunkEndIdx - rb->tail;
    size_t firstChunkReading = (bytesToDequeue < firstChunkRemaining) ? bytesToDequeue : firstChunkRemaining;
    memcpy(data, &rb->buffer[rb->tail], firstChunkReading);
    rb->tail = (rb->tail + firstChunkReading) % rb->bufferSize;
    rb->count -= firstChunkReading;
    bytesToDequeue -= firstChunkReading;
    bytesDequeued += firstChunkReading;

    // 残りデータがなければ終了
    if (bytesToDequeue == 0) {
        return bytesDequeued;
    }

    // 残りデータがある場合はBufferの先頭からheadまでの間を読み込む
    size_t secondChunkReading = bytesToDequeue;
    memcpy(&data[bytesDequeued], &rb->buffer[rb->tail], secondChunkReading);
    rb->tail = (rb->tail + secondChunkReading) % rb->bufferSize;
    rb->count -= secondChunkReading;
    bytesDequeued += secondChunkReading;

    return bytesDequeued;
}