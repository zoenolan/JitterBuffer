
#include <cstddef>
#include "LazyBuffer.h"

int main(int argc, char* argv[])
{
	CLazyBuffer lazyBuffer;

	if (0 != lazyBuffer.CurrentSize())
	{
		return (-1);
	}

	if (NULL != lazyBuffer.Pointer())
	{
		return (-1);
	}

	const int allocSize = 1024;
	lazyBuffer.Resize(allocSize);

	if (NULL == lazyBuffer.Pointer())
	{
		return (-4);
	}

	const int bufferSize = allocSize / 2;
	char buffer[bufferSize];

	lazyBuffer.Copy(buffer, bufferSize);

	if (bufferSize != lazyBuffer.CurrentSize())
	{
		return (-1);
	}

	if (NULL == lazyBuffer.Pointer())
	{
		return (-4);
	}

	return (0);
}

