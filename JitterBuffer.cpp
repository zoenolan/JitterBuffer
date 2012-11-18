
#include <cstddef>
#include <assert.h>

#include "DecoderInterface.h"
#include "RendererInterface.h"

#include "JitterBuffer.h"

CJitterBuffer::CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer)
:   mpDecodedFrame(new char[mOneMegabyte]),
	mLastCompletedFrameReceived(-1),
	mpDecoder(pDecoder),
	mpRenderer(pRenderer)
{
	assert(mpDecoder);
	assert(mpRenderer);
	assert(	mpDecodedFrame);
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
	const bool bFrameInRange      = frameNumber > mLastCompletedFrameReceived;

	assert(bValidPointer);
	assert(bValidBufferLength);
	assert(bFragmentInRange);

	// Sliently drop invalid packets, so the program doesn't crash
	if ((bValidPointer) && (bValidBufferLength) && (bFragmentInRange) && (bFrameInRange))
	{
		mFrame.Reset(numFragmentsInThisFrame);

		mFrame.AddFragment(pBuffer, length, fragmentNumber);

		if (mFrame.Completed())
		{
			mLastCompletedFrameReceived++;

			mFrame.Combine(mRecievedFrame);

			mDecodedFrameSize = mpDecoder->DecodeFrame(mRecievedFrame.Pointer(), mRecievedFrame.CurrentSize(), mpDecodedFrame);

			mpRenderer->RenderFrame(mpDecodedFrame, mDecodedFrameSize);
		}
	}
}

CJitterBuffer::~CJitterBuffer()
{
	if (mpDecodedFrame)
	{
		delete[](mpDecodedFrame);
	}
}
