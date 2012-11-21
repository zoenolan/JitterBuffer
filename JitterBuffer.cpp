
#include <cstddef>
#include <assert.h>

#include "JitterBuffer.h"

#include "Frame/Frame.h"
#include "LazyBuffer/LazyBuffer.h"
#include "RenderBuffer/RenderBuffer.h"
#include "DecoderInterface.h"
#include "RendererInterface.h"

CJitterBuffer::CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer)
:   mLastCompletedFrameReceived(-1),
	mpDecoder(pDecoder),
	mpRenderer(pRenderer)
{
	assert(mpDecoder);
	assert(mpRenderer);
}

void CJitterBuffer::ReceivePacket(const char*	pBuffer,
								  int			length,
								  int			frameNumber,
								  int			fragmentNumber,
								  int			numFragmentsInThisFrame)
{
	const bool bValidPointer      = pBuffer != NULL;
	const bool bValidBufferLength = length > 0;
	const bool bFragmentInRange   = (fragmentNumber >= 0) && (fragmentNumber < numFragmentsInThisFrame);

	assert(bValidPointer);
	assert(bValidBufferLength);
	assert(bFragmentInRange);

	// Sliently drop invalid packets, so the program doesn't crash
	if ((bValidPointer) && (bValidBufferLength) && (bFragmentInRange))
	{
		if (mFrames.find(frameNumber) == mFrames.end())
		{
            // This frame hasn't been started
            const bool bFramesAllocated = mFreeFrames.empty();            
            if (bFramesAllocated)
            {
                // Add a new Frame 			   
			    mFrames[frameNumber] = new CFrame();
            }
            else
            {
                // Reuse an existing Frame
                mFrames[frameNumber] = mFreeFrames.front();
                mFreeFrames.pop_front();
            }

			mFrames[frameNumber]->Reset(numFragmentsInThisFrame);
		}

		mFrames[frameNumber]->AddFragment(pBuffer, length, fragmentNumber);

		if (mFrames[frameNumber]->Completed())
		{
            // Move recieved frames to the decodable queue
			while ((mFrames.find(mLastCompletedFrameReceived + 1) != mFrames.end()) && 
				   (mFrames[mLastCompletedFrameReceived + 1]->Completed()))
			{
                mLastCompletedFrameReceived++;

                CFrame* pFrame = mFrames[mLastCompletedFrameReceived];
                mFrames.erase(mLastCompletedFrameReceived);

                CLazyBuffer* pDecodable = mDecoderQueue.GetFreeBuffer();

                pFrame->Combine(*pDecodable);

                mDecoderQueue.QueueForUse(pDecodable);	

                mFreeFrames.push_back(pFrame);
			}

            serviceDecoder();

            serviceRenderer();
		}
	}
}

void CJitterBuffer::serviceDecoder()
{
    CLazyBuffer* pDecodable = mDecoderQueue.GetUsableBuffer();

    if (pDecodable)
    {
        CRenderBuffer* pRenderable = mRendererQueue.GetFreeBuffer();

        if (pRenderable)
        {
            const int decodedFrameSize = mpDecoder->DecodeFrame(pDecodable->Pointer(), 
                                                                pDecodable->CurrentSize(), 
                                                                pRenderable->Pointer());
            pRenderable->SetSize(decodedFrameSize);

            mRendererQueue.QueueForUse(pRenderable);
        }	
        mDecoderQueue.QueueFreeBuffer(pDecodable);
    }
}

void CJitterBuffer::serviceRenderer()
{
    CRenderBuffer* pRenderable = mRendererQueue.GetUsableBuffer();

    if (pRenderable)
    {
        mpRenderer->RenderFrame(pRenderable->Pointer(), pRenderable->Size());

        mRendererQueue.QueueFreeBuffer(pRenderable);
    }	
}

CJitterBuffer::~CJitterBuffer()
{
    // Clear up the input bitstream data
    while (!mFreeFrames.empty())
    {
        CFrame* pFrame = mFreeFrames.front();
        mFreeFrames.pop_front();

        delete (pFrame);
    }  

    std::map<int, CFrame*>::iterator it;
    for ( it=mFrames.begin() ; it != mFrames.end(); it++ )
    {
        CFrame* pFrame = (*it).second;
        mFrames.erase(it);

        delete (pFrame);
    }  
}
