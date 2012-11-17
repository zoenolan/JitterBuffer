#ifndef _FRAME_H
#define _FRAME_H

#include <vector>

#include "LazyBuffer.h"

class CFrame
{
public:
	CFrame();

	~CFrame();

	void Reset(const int numberOfFragments);

	void AddFragment(const char* pBuffer,
					 const int   length,
					 const int   fragmentNumber);

	bool Completed() const;

	int  SizeInBytes() const;

	int  Combine(const char* pBuffer);

private:
	int					     mNumberOfFragments;

	std::vector<bool>        mReceivedFragments;
	std::vector<CLazyBuffer> mFragments;

	int					     mFrameSizeInBytes;
};

#endif // _FRAME_H