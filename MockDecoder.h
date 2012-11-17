#ifndef _C_MOCK_DECODER_H
#define _C_MOCK_DECODER_H

#include "DecoderInterface.h"

class CMockDecoder: public IDecoder
{
public:
	/*
	Returns the size of the data written to the outputBuffer, will be no more than 1mb.
	*/
	int DecodeFrame(const char* buffer, int length, char* outputBuffer);
};

#endif // _C_MOCK_DECODER_H