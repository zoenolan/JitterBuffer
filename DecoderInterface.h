#ifndef _I_DECODER_H
#define _I_DECODER_H

class IDecoder
{
public:
	/*
	Returns the size of the data written to the outputBuffer, will be no more than 1mb.
	*/
	virtual int DecodeFrame(const char* buffer, int length, char* outputBuffer) = 0;
	
	virtual ~IDecoder() {}
};

#endif // _I_DECODER_H