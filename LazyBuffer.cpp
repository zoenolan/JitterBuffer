
#include "LazyBuffer.h"

#include <cstddef>
#include <cstring>
#include <assert.h>

CLazyBuffer::CLazyBuffer()
:	mAllocatedSize(0),
	mCurrentSize(0),
	mpBuffer(NULL)
{
}

CLazyBuffer::CLazyBuffer(const int allocatedSize)
:	mAllocatedSize(0),
	mCurrentSize(0),
	mpBuffer(NULL)
{
	Resize(allocatedSize);
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
		Resize(length);

		mCurrentSize = length;

		std::memcpy(mpBuffer, pBuffer, length);
	}
}

void CLazyBuffer::Resize (const int length)
{
	const bool bValidLength = length > 0; 

	assert(bValidLength);

	if (bValidLength)
	{
		if (mAllocatedSize < length)
		{
			cleanUpBuffer();
			mpBuffer       = new char[length];
			mAllocatedSize = length;
		}
	}
}

void CLazyBuffer::cleanUpBuffer()
{
	if (mpBuffer)
	{
		delete[] (mpBuffer);
	}
}

char* CLazyBuffer::Pointer() const
{
	return (mpBuffer);
}

int CLazyBuffer::CurrentSize() const
{
	return (mCurrentSize);
}