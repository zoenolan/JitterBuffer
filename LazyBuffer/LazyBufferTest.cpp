
#include <cstddef>
#include <cstdio>
#include "LazyBuffer.h"

int main(int argc, char* argv[])
{
	CLazyBuffer lazyBuffer;

	if (0 != lazyBuffer.CurrentSize())
	{
		printf("Failed: The Buffer should start as zero sized\n");
		return (-1);
	}

	if (NULL != lazyBuffer.Pointer())
	{
		printf("Failed: The Buffer pointer should be NULL at the start of day\n");
		return (-1);
	}

	const int allocSize = 1024;
	lazyBuffer.Resize(allocSize);

	if (NULL == lazyBuffer.Pointer())
	{
		printf("Failed: The Buffer pointer should not be NULL once a size is allocated\n");
		return (-4);
	}

	const int bufferSize = allocSize / 2;
	char buffer[bufferSize];

	lazyBuffer.Copy(buffer, bufferSize);

	if (bufferSize != lazyBuffer.CurrentSize())
	{
		printf("Failed: The Buffer size should match the allocated size\n");
		return (-1);
	}

	if (NULL == lazyBuffer.Pointer())
	{
		printf("Failed: The Buffer pointer should not be NULL once a size is allocated\n");
		return (-1);
	}

	printf("Passed\n");
	return (0);
}

