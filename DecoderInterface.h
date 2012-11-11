#ifndef _I_DECODER_H
#define _I_DECODER_H

class IDecoder
{
public:
	/*
	Returns the size of the data written to the outputBuffer, will be no more than 1mb.
	*/
	virtual unsigned int DecodeFrame(const char* pInputBuffer, const unsigned int length, char* pOutputBuffer) = 0;
	
	virtual ~IDecoder() {}
};

#endif // _I_DECODER_H