#ifndef _C_MOCK_DECODER_H
#define _C_MOCK_DECODER_H

#include "IDecoder.h"

class CMockDecoder: public IDecoder
{
public:
	/*
	Returns the size of the data written to the outputBuffer, will be no more than 1mb.
	*/
	unsigned int DecodeFrame(const char* pInputBuffer, const unsigned int length, char* pOutputBuffer);
};

#endif // _C_MOCK_DECODER_H