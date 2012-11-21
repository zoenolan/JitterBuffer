#ifndef _LAZY_BUFFER_H
#define _LAZY_BUFFER_H

class CFrame;

class CLazyBuffer
{
public:
	CLazyBuffer();
	~CLazyBuffer();

    CLazyBuffer( const CLazyBuffer& rhs );           
    CLazyBuffer& operator=( const CLazyBuffer& rhs); 

	/*
	Copy the contents of the pointer into the internal buffer
	@param pBuffer - pointer to the fragments data
	@param length  - length of the fragment
	*/
	void Copy(const char* pBuffer, const int length);

	/*
	Resize the allocation to length
	@param length  - length of the fragment
	*/
	void Resize (const int length);

	/*
	Return a pointer to the current allocation
	*/
	char* Pointer() const;

	/*
	Return the size in bytes of the current allocation
	*/
	int   CurrentSize() const;

    friend class CFrame;

protected:
	/*
	Resize the allocation and set the current size to length
	@param length  - length of the fragment
	*/
	void SetCurrentSize(const int length);

	/*
	Copy the contents of the pointer into the internal buffer, starting from offset
	@param pBuffer - pointer to the fragments data
	@param length  - length of the fragment
	@param offset  - offset from the start of the internal buffer
	*/
	void SubCopy(const char* pBuffer, const int length, const int offset);

private:
	void cleanUpBuffer();

	int mAllocatedSize;
	int mCurrentSize;

	char*  mpBuffer;
};

#endif // _LAZY_BUFFER_H
