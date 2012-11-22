#ifndef _RENDER_BUFFER_H
#define _RENDER_BUFFER_H

#include "../LazyBuffer/LazyBuffer.h"

class CRenderBuffer : public CLazyBuffer
{
public:
	CRenderBuffer();

	/*
	Set the current size to size
	@param size - will start at zero for the call
	*/
	void  SetSize(const int size);

private:
	static const int mOneMegabyte = 1024 * 1024;

	static const int mAllocSize = mOneMegabyte;
};

#endif // _RENDER_BUFFER_H
