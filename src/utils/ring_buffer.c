#include "ring_buffer.h"
#include "rtos_wrapper.h"
#include "typedef.h"

/****************************************************
 * forward declaration
 ****************************************************/
bool ringBufferInit(ringBuffer_t *rb, uint8_t *buffer, size_t bufferSize);
size_t ringBufferAvailableSize(ringBuffer_t *rb);
void ringBufferClear(ringBuffer_t *rb);
int32_t ringBufferEnqueue(ringBuffer_t *rb, const uint8_t *data, size_t len);
int32_t ringBufferDequeue(ringBuffer_t *rb, uint8_t *data, size_t len);

bool ringBufferInit(ringBuffer_t *rb, uint8_t *buffer, size_t bufferSize)
{
    if (rb == NULL || buffer == NULL || bufferSize == 0)
    {
        return false;
    }
    rb->buffer = buffer;
    rb->bufferSize = bufferSize;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    rb->mtx = rtos_mutex_create();
    return true;
}

size_t ringBufferAvailableSize(ringBuffer_t *rb)
{
    if (rb == NULL)
    {
        return 0;
    }
    return rb->bufferSize - rb->count;
}

void ringBufferClear(ringBuffer_t *rb)
{
    rtos_mutex_take(rb->mtx);
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    memset(rb->buffer, 0, rb->bufferSize);
    rtos_mutex_give(rb->mtx);
}

int32_t ringBufferEnqueue(ringBuffer_t *rb, const uint8_t *data, size_t len)
{
    rtos_mutex_take(rb->mtx);
    int32_t ret = E_OTHER;

    if (rb == NULL || data == NULL || len == 0)
    {
        ret = E_ARGUMENT;
        goto exit;
    }
    size_t bytesToEnqueue =
        (len < ringBufferAvailableSize(rb)) ? len : ringBufferAvailableSize(rb);

    if (bytesToEnqueue == 0)
    {
        ret = E_WOULDBLOCK; // バッファがいっぱい
        goto exit;
    }
    size_t bytesEnqueued = 0;

    // バッファの末尾まで書き込めるサイズを計算し、memcpyで書き込む
    size_t firstChunkRemaining = rb->bufferSize - rb->head;
    size_t firstChunkWriting = (bytesToEnqueue < firstChunkRemaining)
                                   ? bytesToEnqueue
                                   : firstChunkRemaining;
    memcpy(&rb->buffer[rb->head], data, firstChunkWriting);
    rb->head = (rb->head + firstChunkWriting) % rb->bufferSize;
    rb->count += firstChunkWriting;
    bytesToEnqueue -= firstChunkWriting;
    bytesEnqueued += firstChunkWriting;

    // 残りデータがなければ終了
    if (bytesToEnqueue == 0)
    {
        ret = bytesEnqueued;
        goto exit;
    }

    // 残りのデータがある場合はBufferの先頭から書き込む
    memcpy(&rb->buffer[rb->head], &data[bytesEnqueued], bytesToEnqueue);
    rb->head = (rb->head + bytesToEnqueue) % rb->bufferSize;
    rb->count += bytesToEnqueue;
    bytesEnqueued += bytesToEnqueue;
    ret = bytesEnqueued;

exit:
    rtos_mutex_give(rb->mtx);
    return ret;
}

int32_t ringBufferDequeue(ringBuffer_t *rb, uint8_t *data, size_t len)
{
    rtos_mutex_take(rb->mtx);
    int32_t ret = E_OTHER;

    if (rb == NULL || data == NULL || len == 0)
    {
        ret = E_ARGUMENT;
        goto exit;
    }
    size_t bytesToDequeue = (len < rb->count) ? len : rb->count;

    if (bytesToDequeue == 0)
    {
        ret = E_WOULDBLOCK; // バッファが空
        goto exit;
    }
    size_t bytesDequeued = 0;

    // tail --> head or tail --> buffer end
    // まで読み込めるサイズを計算し、memcpyで読み込む
    size_t firstChunkEndIdx = (rb->head > rb->tail) ? rb->head : rb->bufferSize;
    size_t firstChunkRemaining = firstChunkEndIdx - rb->tail;
    size_t firstChunkReading = (bytesToDequeue < firstChunkRemaining)
                                   ? bytesToDequeue
                                   : firstChunkRemaining;
    memcpy(data, &rb->buffer[rb->tail], firstChunkReading);
    rb->tail = (rb->tail + firstChunkReading) % rb->bufferSize;
    rb->count -= firstChunkReading;
    bytesToDequeue -= firstChunkReading;
    bytesDequeued += firstChunkReading;

    // 残りデータがなければ終了
    if (bytesToDequeue == 0)
    {
        ret = bytesDequeued;
        goto exit;
    }

    // 残りデータがある場合はBufferの先頭からheadまでの間を読み込む
    size_t secondChunkReading = bytesToDequeue;
    memcpy(&data[bytesDequeued], &rb->buffer[rb->tail], secondChunkReading);
    rb->tail = (rb->tail + secondChunkReading) % rb->bufferSize;
    rb->count -= secondChunkReading;
    bytesDequeued += secondChunkReading;

exit:
    rtos_mutex_give(rb->mtx);
    return ret;
}
