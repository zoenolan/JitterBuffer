#ifndef _C_BUFFER_QUEUE_H
#define _C_BUFFER_QUEUE_H

#include <deque>
#include "windows.h"

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

	HANDLE			 mFreeMutex;
	HANDLE			 mUsableMutex;
};

template <class T> CBufferQueue<T>::CBufferQueue()
:	mFreeMutex(CreateMutex(NULL, FALSE, NULL )),
	mUsableMutex(CreateMutex(NULL, FALSE, NULL ))
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

	CloseHandle(mFreeMutex);
	CloseHandle(mUsableMutex);
}

template <class T> T* CBufferQueue<T>::GetFreeBuffer()
{
	WaitForSingleObject(mFreeMutex, INFINITE);
    const bool bFramesToReuse = !mFreeBuffers.empty();
	ReleaseMutex(mFreeMutex);

    T* pDecodable;

    if (bFramesToReuse)
    {
		WaitForSingleObject(mFreeMutex, INFINITE);

        // Reuse an existing Frame
        pDecodable = mFreeBuffers.front();
        mFreeBuffers.pop_front();

		ReleaseMutex(mFreeMutex);
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
	WaitForSingleObject(mFreeMutex, INFINITE);
    mFreeBuffers.push_back(pBuffer);
	ReleaseMutex(mFreeMutex);
}

template <class T> T* CBufferQueue<T>::GetUsableBuffer()
{
	// wait for a buffer to be queued
	WaitForSingleObject(mUsableMutex, INFINITE);
	bool bBuffersWaiting = !mUsableBuffers.empty();
	ReleaseMutex(mUsableMutex);

    while (bBuffersWaiting)
    {
		WaitForSingleObject(mUsableMutex, INFINITE);
		bBuffersWaiting = !mUsableBuffers.empty();
		ReleaseMutex(mUsableMutex);
	}

	WaitForSingleObject(mUsableMutex, INFINITE);

    T* pDecodable = mUsableBuffers.front();
    mUsableBuffers.pop_front();

	ReleaseMutex(mUsableMutex);

    return (pDecodable);
}

template <class T> void CBufferQueue<T>::QueueForUse(T* pBuffer)
{
	WaitForSingleObject(mUsableMutex, INFINITE);
    mUsableBuffers.push_back(pBuffer);
	ReleaseMutex(mUsableMutex);
}

#endif // _C_BUFFER_QUEUE_H
