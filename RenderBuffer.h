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
	int				mCurrentSize;
	char*			mpBuffer;

	static const int mOneMegabyte = 1024 * 1024;
};

#endif // _RENDER_BUFFER_H