#ifndef _LAZY_BUFFER_H
#define _LAZY_BUFFER_H

class CLazyBuffer
{
public:
	CLazyBuffer();
	~CLazyBuffer();

	void Copy(const char* pBuffer, const int length);

	void Resize (const int length);

	char* Pointer() const;
	int   CurrentSize() const;

private:
	void cleanUpBuffer();

	int mAllocatedSize;
	int mCurrentSize;

	char*  mpBuffer;

    CLazyBuffer( const CLazyBuffer& rhs );           // non construction-copyable
    CLazyBuffer& operator=( const CLazyBuffer& rhs); // non copyable
};

#endif // _LAZY_BUFFER_H