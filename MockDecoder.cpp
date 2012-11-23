#include <assert.h>
#include <windows.h>

#include "MockDecoder.h"

int CMockDecoder::DecodeFrame(const char* buffer, int length, char* outputBuffer)
{
	Sleep(15);
	return (length);
}
