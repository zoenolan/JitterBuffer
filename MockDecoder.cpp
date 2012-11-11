#include <assert.h>

#include "MockDecoder.h"

unsigned int CMockDecoder::DecodeFrame(const char* pInputBuffer, const unsigned int length, char* pOutputBuffer)
{
	assert(pInputBuffer);
	assert(pOutputBuffer);

	return (0);
}
