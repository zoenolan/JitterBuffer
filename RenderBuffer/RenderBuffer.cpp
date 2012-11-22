
#include <assert.h>
#include "RenderBuffer.h"

CRenderBuffer::CRenderBuffer()
{
	SetCurrentSize(mAllocSize);
}

void CRenderBuffer::SetSize(const int size)
{
	const bool bNegativeSize = size < 0;
	const bool bOverFlow     = size > mAllocSize;

	assert(!bNegativeSize);
	assert(!bOverFlow);

	if (bNegativeSize)
	{
		SetCurrentSize(0);
	}
	else if (bOverFlow)
	{
		SetCurrentSize(mAllocSize);
	}
	else
	{
		SetCurrentSize(size);
	}
}
