
#include <assert.h>

#include "DecoderInterface.h"
#include "RendererInterface.h"
/*
#include "JitterBuffer.h"

CJitterBuffer::CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer)
: mpDecoder(pDecoder),
  mpRenderer(pRenderer)
{
	assert(mpDecoder);
	assert(mpRenderer);
}

void CJitterBuffer::ReceivePacket( 
	                    const char*        pBuffer,
						const unsigned int length,
						const unsigned int frameNumber,
						const unsigned int fragmentNumber,
						const unsigned int numFragmentsInThisFrame)
{
	assert(pBuffer);
	assert(length > 0);
	assert(fragmentNumber < numFragmentsInThisFrame);

	// Is this frame already being processed?
	if (!frameBeingProcessed(frameNumber))
	{
		// Try to find an available frame on the free queue
		if ()
		{

		}
		else
		{
			// No free frames, allocate a new one 
		}
	}

	// Add the current fragment

	// Is the Frame completed
}

CJitterBuffer::~CJitterBuffer()
{

}

bool CJitterBuffer::frameBeingProcessed(const unsigned int frameNumber)
{
	return (false);
}
*/