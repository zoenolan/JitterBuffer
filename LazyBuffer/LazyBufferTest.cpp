
#include <cstddef>
#include <cstdio>
#include <cstring> 
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

	CLazyBuffer secondLazyBuffer(lazyBuffer);

	if (0 != secondLazyBuffer.CurrentSize())
	{
		printf("Failed: The Buffer should start as zero sized\n");
		return (-1);
	}

	if (NULL != secondLazyBuffer.Pointer())
	{
		printf("Failed: The Buffer pointer should be NULL at the start of day\n");
		return (-1);
	}

	CLazyBuffer thirdLazyBuffer = lazyBuffer;

	if (0 != thirdLazyBuffer.CurrentSize())
	{
		printf("Failed: The Buffer should start as zero sized\n");
		return (-1);
	}

	if (NULL != thirdLazyBuffer.Pointer())
	{
		printf("Failed: The Buffer pointer should be NULL at the start of day\n");
		return (-1);
	}

	memset(buffer, 1, bufferSize);
	lazyBuffer.Copy(buffer, bufferSize);

	char* pInternalBuffer = lazyBuffer.Pointer();

	for (int i = 0; i < bufferSize; i++)
	{
		if (1 != pInternalBuffer[i])
		{
			printf("Failed: The Buffer contents do not match\n");
			return (-1);
		}
	}

	printf("Passed\n");
	return (0);
}

