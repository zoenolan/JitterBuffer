// JitterBuffer.cpp : Defines the entry point for the console application.
//

// Interfaces
#include "DecoderInterface.h"
#include "RendererInterface.h"
#include "JitterBufferInterface.h"

// Mocks
#include "MockDecoder.h"
#include "MockRenderer.h"

// Class being tested
#include "JitterBuffer.h"

int main(int argc, char* argv[])
{
	const int bufferSize = 1024;
	char buffer[bufferSize];

	const int fragmentsPerFrame = 10;

	const int framesToTest = 10;

	IDecoder*  pDecoder          = new CMockDecoder();
	IRenderer* pRenderer         = new CMockRenderer();

	IJitterBuffer* pJitterBuffer = new CJitterBuffer(pDecoder, pRenderer);

	for (int frame = 0; frame < framesToTest; frame++)
	{
		for (int fragment = 0; fragment < fragmentsPerFrame; fragment++)
		{
			pJitterBuffer->ReceivePacket(buffer, bufferSize, frame, fragment, fragmentsPerFrame);
		}
	}

	delete (pJitterBuffer);

	delete (pRenderer);
	delete (pDecoder);
	
	return (0);
}

