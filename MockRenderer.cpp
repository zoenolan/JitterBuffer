#include <assert.h>

#include "MockRenderer.h"

void CMockRenderer::RenderFrame(const char* pBuffer, const unsigned int length)
{
	assert(pBuffer);
	assert(length > 0);
}