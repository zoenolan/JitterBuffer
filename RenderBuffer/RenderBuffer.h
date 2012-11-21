#ifndef _RENDER_BUFFER_H
#define _RENDER_BUFFER_H

class CRenderBuffer
{
public:
	CRenderBuffer();
	~CRenderBuffer();

	/*
	Set the current size to size
	@param size - will start at zero for the call
	*/
	void  SetSize(const int size);

	/*
	Return the size in bytes of the current allocation
	*/
	int   Size() const;

	/*
	Return a pointer to the current allocation
	*/
	char* Pointer() const;

private:
	int				 mCurrentSize;
	char*			 mpBuffer;

	static const int mOneMegabyte = 1024 * 1024;

    CRenderBuffer( const CRenderBuffer& rhs );           // non construction-copyable
    CRenderBuffer& operator=( const CRenderBuffer& rhs); // non copyable
};

#endif // _RENDER_BUFFER_H
