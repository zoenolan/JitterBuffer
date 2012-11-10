
#include "IDecoder.h"
#include "IRenderer.h"
#include "CJitterBuffer.h"

CJitterBuffer::CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer)
: mpDecoder(pDecoder),
  mpRenderer(pRenderer)
{
}

void CJitterBuffer::ReceivePacket( 
	                    const char*        pBuffer,
						const unsigned int length,
						const unsigned int frameNumber,
						const unsigned int fragmentNumber,
						const unsigned int numFragmentsInThisFrame)
{

}

CJitterBuffer::~CJitterBuffer()
{

}
