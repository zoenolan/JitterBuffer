
#include <cstdio>
#include "RenderBuffer.h"

int main(int argc, char* argv[])
{
	CRenderBuffer renderBuffer;

	const int oneMegabyte = 1024 * 1024;

	const int testSize[][2] = 
	{
		// Value			Expected

		// test negative size
		{-1,						  0},

		// test greater than buffer sized
		{2 * oneMegabyte,	oneMegabyte},
	};

	const char* testErrorStrings[] =
	{
		"Failed: Setting a negative size\n",
		"Failed: Setting a size larger than the allocation\n",
	};

	const int numberOfTestCases = sizeof (testSize)/ (sizeof(int) * 2);

	// Test out of range values
	for (int i = 0; i < numberOfTestCases; i++)
	{
		renderBuffer.SetSize(testSize[i][0]);

		if (renderBuffer.Size() != testSize[i][1])
		{
			printf("%s", testErrorStrings[i]);
			return (-1);
		}
	}

	// Test in range values
	const int stepSize = oneMegabyte/1024;
	for (int i = 0; i < oneMegabyte; i+= stepSize)
	{
		renderBuffer.SetSize(i);

		if (renderBuffer.Size() != i)
		{
			printf("Failed: Setting the size to %d\n", i);
			return (-1);
		}
	}

	printf("Passed\n");
	return (0);
}

