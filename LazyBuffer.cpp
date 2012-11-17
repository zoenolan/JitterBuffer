
#include "LazyBuffer.h"

#include <cstddef>
#include <cstring>
#include <assert.h>

CLazyBuffer::CLazyBuffer(const size_t sizeInBytes)
:	mAllocatedSize(0),
	mCurrentSize(0),
	mpBuffer(NULL)
{
}

CLazyBuffer::~CLazyBuffer()
{
	cleanUpBuffer();
}

void CLazyBuffer::Copy(const char* pBuffer, const int length)
{
	const bool bValidBuffer = pBuffer != NULL;
	const bool bValidLength = length > 0; 

	assert(bValidBuffer);
	assert(bValidLength);

	if (bValidBuffer && bValidLength)
	{
		if (mAllocatedSize < length)
		{
			cleanUpBuffer();
			mpBuffer       = new char[length];
			mAllocatedSize = length;
		}

		mCurrentSize = length;

		std::memcpy(mpBuffer, pBuffer, length);
	}
}

void CLazyBuffer::cleanUpBuffer()
{
	if (mpBuffer)
	{
		delete[] (mpBuffer);
	}
}