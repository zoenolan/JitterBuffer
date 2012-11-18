
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

		// test zero sized buffer
		{0,							  0},

		// test a valid value
		{512,						512},

		// test exactly buffer sized
		{oneMegabyte,		oneMegabyte},

		// test greater than buffer sized
		{2 * oneMegabyte,	oneMegabyte},
	};

	const int numberOfTestCases = sizeof (testSize)/ (sizeof(int) * 2);

	for (int i = 0; i < numberOfTestCases; i++)
	{
		renderBuffer.SetSize(testSize[i][0]);

		if (renderBuffer.Size() != testSize[i][1])
		{
			return (-1);
		}
	}

	return (0);
}

