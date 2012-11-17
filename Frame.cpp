
#include "Frame.h"

#include <assert.h>

CFrame::CFrame()
:
	mFragmentsRemaining(0),
    mFrameSizeInBytes(0)
{
}

void CFrame::Reset(const int numberOfFragments)
{
	mFragmentsRemaining = numberOfFragments;

	mSeenFragment.reserve(numberOfFragments);
	std::fill(mSeenFragment.begin(), mSeenFragment.end(), false);

	mFragments.reserve(numberOfFragments);

	mFrameSizeInBytes = 0;
}

void CFrame::AddFragment(const char* pBuffer,
						 const int   length,
					     const int   fragmentNumber)
{
	const bool bFragmentsRemaining     = mFragmentsRemaining > 0;
	const bool bFragmentNotSeenAlready = !mSeenFragment[fragmentNumber]; 

	assert(bFragmentsRemaining);

	if (bFragmentsRemaining)
	{
		mFragments[fragmentNumber].Copy(pBuffer, length);
		mSeenFragment[fragmentNumber] = true;

		mFragmentsRemaining--;
		mFrameSizeInBytes += length;
	}
}

bool CFrame::Completed() const
{
	return (0 == mFragmentsRemaining);
}

int  CFrame::SizeInBytes() const
{
	return (mFrameSizeInBytes);
}

int  CFrame::Combine(const char* pBuffer)
{
	return (0);
}