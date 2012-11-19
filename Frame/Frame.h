#ifndef _FRAME_H
#define _FRAME_H

#include <vector>

#include "../LazyBuffer/LazyBuffer.h"

class CFrame
{
public:
	CFrame();

	void Reset(const int numberOfFragments);

	void AddFragment(const char* pBuffer,
					 const int   length,
					 const int   fragmentNumber);

	bool Completed() const;

	void Combine(CLazyBuffer& outputBuffer);

private:
	int					     mFragmentsRemaining;

	std::vector<bool>        mSeenFragment;
	std::vector<CLazyBuffer> mFragments;

	int					     mFrameSizeInBytes;

    CFrame( const CFrame& rhs );           // non construction-copyable
    CFrame& operator=( const CFrame& rhs); // non copyable
};

#endif // _FRAME_H