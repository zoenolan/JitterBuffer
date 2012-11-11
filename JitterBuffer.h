#ifndef _C_JITTER_BUFFER_H
#define _C_JITTER_BUFFER_H

#include "IJitterBuffer.h"

class CJitterBuffer : public IJitterBuffer
{
public:
	CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer);
	
	/*
	Should copy the given buffer, as it may be deleted/reused immediately following this call.
	@param frameNumber - will start at zero for the call
	@param fragmentNumber – specifies what position this fragment is within the given
	frame – the first fragment number in each frame is number zero
	@param numFragmentsInThisFrame - is guaranteed to be identical for all fragments
	with the same frameNumber
	*/
	void ReceivePacket( const char*        pBuffer,
						const unsigned int length,
						const unsigned int frameNumber,
						const unsigned int fragmentNumber,
						const unsigned int numFragmentsInThisFrame);
	
	~CJitterBuffer();

private:
	IDecoder*  mpDecoder;
	IRenderer* mpRenderer;
};

#endif // _C_JITTER_BUFFER_H