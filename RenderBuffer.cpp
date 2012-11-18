
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
	mCurrentSize = size;
}

int CRenderBuffer::Size() const
{
	return (mCurrentSize);
}

char* CRenderBuffer::Pointer() const
{
	return (mpBuffer);
}