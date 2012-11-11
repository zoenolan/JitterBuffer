#ifndef _C_MOCK_RENDERER_H
#define _C_MOCK_RENDERER_H

#include "RendererInterface.h"

class CMockRenderer: public IRenderer
{
public:
	/*
	Renders the given buffer. This call will not block for any significant period, and
	the buffer will be copied internally so can be deleted/reused as soon as this call
	is completed.
	*/
	void RenderFrame(const char* pBuffer, const unsigned int length);
};

#endif // _C_MOCK_RENDERER_H