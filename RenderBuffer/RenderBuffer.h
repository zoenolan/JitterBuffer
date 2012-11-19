#ifndef _RENDER_BUFFER_H
#define _RENDER_BUFFER_H

class CRenderBuffer
{
public:
	CRenderBuffer();
	~CRenderBuffer();

	void  SetSize(const int size);
	int   Size() const;

	char* Pointer() const;

private:
	int				 mCurrentSize;
	char*			 mpBuffer;

	static const int mOneMegabyte = 1024 * 1024;

    CRenderBuffer( const CRenderBuffer& rhs );           // non construction-copyable
    CRenderBuffer& operator=( const CRenderBuffer& rhs); // non copyable
};

#endif // _RENDER_BUFFER_H