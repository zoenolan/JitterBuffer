#ifndef _C_BUFFER_QUEUE_H
#define _C_BUFFER_QUEUE_H

#include <deque>

template <class T> class CBufferQueue
{
public:
    CBufferQueue();
    ~CBufferQueue();

    T* GetFreeBuffer();
    void         QueueFreeBuffer(T* pBuffer);  

    T* GetUsableBuffer();
    void         QueueForUse(T* pBuffer);

private:
    std::deque<T*>   mFreeBuffers;
    std::deque<T*>   mUsableBuffers;
};

#endif // _C_BUFFER_QUEUE_H
