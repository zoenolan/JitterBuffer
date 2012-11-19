
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

CLazyBuffer::~CLazyBuffer()
{
	cleanUpBuffer();
}

CLazyBuffer::CLazyBuffer( const CLazyBuffer& rhs )
:	mAllocatedSize(0),
	mCurrentSize(0),
	mpBuffer(NULL)
{
}

CLazyBuffer& CLazyBuffer::operator=( const CLazyBuffer& rhs)
{
	mAllocatedSize = 0;
	mCurrentSize   = 0;
	mpBuffer       = NULL;

	return (*this);
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

		mCurrentSize   = length;

		std::memcpy(mpBuffer, pBuffer, length);
	}
}

void CLazyBuffer::SubCopy(const char* pBuffer, const int length, const int offset)
{
	const bool bValidBuffer = pBuffer != NULL;
	const bool bValidLength = length > 0; 
	const bool bValidSize   = (offset + length) <= mCurrentSize;

	assert(bValidBuffer);
	assert(bValidLength);
	assert(bValidSize);

	if (bValidBuffer && bValidLength && bValidSize)
	{
		std::memcpy(mpBuffer + offset, pBuffer, length);
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