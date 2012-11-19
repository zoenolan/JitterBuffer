
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
		printf("Failed: The Frame should not be completed after reset has been calledn");
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

/*
	void Combine(CLazyBuffer& outputBuffer);
*/
	printf("Passed\n");
	return (0);
}

