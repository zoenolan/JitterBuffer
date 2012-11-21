
#include "BufferQueue.h"

template <class T> CBufferQueue<T>::CBufferQueue()
{

}

template <class T> CBufferQueue<T>::~CBufferQueue()
{
    while (!mFreeBuffers.empty())
    {
        T* pBuffer = mFreeBuffers.front();
        mFreeBuffers.pop_front();

        delete (pBuffer);
    }  

    while (!mUsableBuffers.empty())
    {
        T* pBuffer = mUsableBuffers.front();
        mUsableBuffers.pop_front();

        delete (pBuffer);
    }
}

template <class T> T* CBufferQueue<T>::GetFreeBuffer()
{
    const bool bFramesToReuse = !mFreeBuffers.empty();

    T* pDecodable;

    if (bFramesToReuse)
    {
        // Reuse an existing Frame
        pDecodable = mFreeBuffers.front();
        mFreeBuffers.pop_front();
    }
    else
    {
        // Add a new Frame 			   
        pDecodable = new T();
    }

    return (pDecodable);
}

template <class T> void CBufferQueue<T>::QueueFreeBuffer(T* pBuffer)
{
    mFreeBuffers.push_back(pBuffer);
}

template <class T> T* CBufferQueue<T>::GetUsableBuffer()
{
    const bool bFramesToReuse = !mUsableBuffers.empty();

    if (bFramesToReuse)
    {
        // Reuse an existing Frame
        T* pDecodable = mUsableBuffers.front();
        mUsableBuffers.pop_front();
        return (pDecodable);
    }
    else
    {
        return (NULL);
    }
}

template <class T> void CBufferQueue<T>::QueueForUse(T* pBuffer)
{
    mUsableBuffers.push_back(pBuffer);
}
