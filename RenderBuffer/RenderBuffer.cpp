
#include <assert.h>
#include "RenderBuffer.h"

CRenderBuffer::CRenderBuffer()
:	mCurrentSize(0),
	mpBuffer(new char[mOneMegabyte])
{
}

CRenderBuffer::~CRenderBuffer()
{
	if (mpBuffer)
	{
		delete[](mpBuffer);
	}
}

void CRenderBuffer::SetSize(const int size)
{
	const bool bNegativeSize = size < 0;
	const bool bOverFlow     = size > mOneMegabyte;

	assert(!bNegativeSize);
	assert(!bOverFlow);

	if (bNegativeSize)
	{
		mCurrentSize = 0;
	}
	else if (bOverFlow)
	{
		mCurrentSize = mOneMegabyte;
	}
	else
	{
		mCurrentSize = size;
	}
}

int CRenderBuffer::Size() const
{
	return (mCurrentSize);
}

char* CRenderBuffer::Pointer() const
{
	return (mpBuffer);
}