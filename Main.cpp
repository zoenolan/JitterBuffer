// JitterBuffer.cpp : Defines the entry point for the console application.
//

// Interfaces
#include "IDecoder.h"
#include "IRenderer.h"
#include "IJitterBuffer.h"

// Mocks
#include "CMockDecoder.h"
#include "CMockRenderer.h"

// Class being tested
#include "CJitterBuffer.h"

int main(int argc, char* argv[])
{
	IDecoder*  pDecoder          = new CMockDecoder();
	IRenderer* pRenderer         = new CMockRenderer();

	IJitterBuffer* pJitterBuffer = new CJitterBuffer(pDecoder, pRenderer);

	delete (pJitterBuffer);

	delete (pRenderer);
	delete (pDecoder);

	return 0;
}

