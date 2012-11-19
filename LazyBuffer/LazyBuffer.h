#ifndef _LAZY_BUFFER_H
#define _LAZY_BUFFER_H

class CLazyBuffer
{
public:
	CLazyBuffer();
	~CLazyBuffer();

    CLazyBuffer( const CLazyBuffer& rhs );           
    CLazyBuffer& operator=( const CLazyBuffer& rhs); 

	void Copy(const char* pBuffer, const int length);
	void SubCopy(const char* pBuffer, const int length, const int offset);

	void Resize (const int length);

	char* Pointer() const;
	int   CurrentSize() const;


private:
	void cleanUpBuffer();

	int mAllocatedSize;
	int mCurrentSize;

	char*  mpBuffer;
};

#endif // _LAZY_BUFFER_H