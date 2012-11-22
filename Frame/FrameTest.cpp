
#include "Frame.h"

int main(int argc, char* argv[])
{
	CFrame frame;

	if (!frame.Completed())
	{
		printf("Failed: The Frame should be completed at construction time\n");
		return (-1);
	}

	frame.Reset(1);

	if (frame.Completed())
	{
		printf("Failed: The Frame should not be completed after reset has been called\n");
		return (-1);
	}

	const int bufferSize = 128;
	char buffer[bufferSize];

	frame.AddFragment(buffer, bufferSize, 0);

	if (!frame.Completed())
	{
		printf("Failed: The Frame should be completed after all the frgments have been added\n");
		return (-1);
	}

	const int fragmentsPerFrame = 10;
	frame.Reset(fragmentsPerFrame);

	if (frame.Completed())
	{
		printf("Failed: The Frame should not be completed after reset has been called\n");
		return (-1);
	}

	for (int i = 0; i < fragmentsPerFrame; i++)
	{
		frame.AddFragment(buffer, bufferSize, i);
	}

	if (!frame.Completed())
	{
		printf("Failed: The Frame should be completed after all the frgments have been added\n");
		return (-1);
	}

	CLazyBuffer outputBuffer;

	frame.Combine(outputBuffer);

	if ((fragmentsPerFrame*bufferSize) != outputBuffer.Size())
	{
		printf("Failed: The combined buffer is the wrong size\n");
		return (-1);
	}

	printf("Passed\n");
	return (0);
}

