
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

	// Test basic operation
	for (int frame = 0; frame < framesToTest; frame++)
	{
		for (int fragment = 0; fragment < fragmentsPerFrame; fragment++)
		{
			pJitterBuffer->ReceivePacket(buffer, bufferSize, frame, fragment, fragmentsPerFrame);
		}
	}

	// Test late frames
	for (int fragment = 1; fragment < fragmentsPerFrame; fragment++)
	{
		pJitterBuffer->ReceivePacket(buffer, bufferSize, framesToTest, fragment, fragmentsPerFrame);
	}

	for (int frame = framesToTest + 1 ; frame < framesToTest + 11; frame++)
	{
		for (int fragment = 0; fragment < fragmentsPerFrame; fragment++)
		{
			pJitterBuffer->ReceivePacket(buffer, bufferSize, frame, fragment, fragmentsPerFrame);
		}
	}

	pJitterBuffer->ReceivePacket(buffer, bufferSize, framesToTest, 0, fragmentsPerFrame);

	for (int frame = framesToTest + 11; frame < framesToTest + 20; frame++)
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

