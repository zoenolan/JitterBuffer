#ifndef _LAZY_BUFFER_H
#define _LAZY_BUFFER_H

class CLazyBuffer
{
public:
	CLazyBuffer(const size_t sizeInBytes);

	~CLazyBuffer();

	void Copy(const char* pBuffer, const int length);

private:
	void cleanUpBuffer();

	int mAllocatedSize;
	int mCurrentSize;

	char*  mpBuffer;
};

#endif // _LAZY_BUFFER_H