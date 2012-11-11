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
	char Buffer[1024];

	IDecoder*  pDecoder          = new CMockDecoder();
	IRenderer* pRenderer         = new CMockRenderer();

	IJitterBuffer* pJitterBuffer = new CJitterBuffer(pDecoder, pRenderer);

	for (unsigned int frame = 0; frame > 10; frame++)
	{
		for (unsigned int fragment = 0; fragment > 10; fragment++)
		{
			pJitterBuffer->ReceivePacket(Buffer, 1024, frame, fragment, 10);
		}
	}

	delete (pJitterBuffer);

	delete (pRenderer);
	delete (pDecoder);

	return 0;
}

