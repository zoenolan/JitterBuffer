
#include <assert.h>

#include "Frame.h"

CFrame::CFrame()
:
	mFragmentsRemaining(0),
    mFrameSizeInBytes(0)
{
	QueryPerformanceFrequency(&mTimerFrequency);
}

void CFrame::Reset(const int numberOfFragments)
{
	mFragmentsRemaining = numberOfFragments;

	mSeenFragment.resize(numberOfFragments);
	std::fill(mSeenFragment.begin(), mSeenFragment.end(), false);

	mFragments.resize(numberOfFragments);

	mFrameSizeInBytes = 0;

	QueryPerformanceCounter(&mStartTime);
}

void CFrame::AddFragment(const char* pBuffer,
						 const int   length,
					     const int   fragmentNumber)
{
	const bool bFragmentsRemaining     = mFragmentsRemaining > 0;
	const bool bFragmentNotSeenAlready = !(mSeenFragment[fragmentNumber]); 

	assert(bFragmentsRemaining);
	assert(bFragmentNotSeenAlready);

	if (bFragmentsRemaining && bFragmentNotSeenAlready)
	{
		mFragments[fragmentNumber].Copy(pBuffer, length);
		mSeenFragment[fragmentNumber] = true;

		mFragmentsRemaining--;
		mFrameSizeInBytes += length;

		if (0 == mFragmentsRemaining)
		{
			QueryPerformanceCounter(&mEndTime);
		}
	}
}

bool CFrame::Completed() const
{
	return (0 == mFragmentsRemaining);
}

void CFrame::Combine(CLazyBuffer& outputBuffer)
{
    if (Completed())
    {
	    outputBuffer.SetCurrentSize(mFrameSizeInBytes);

	    int  offset = 0;
	    for (size_t i = 0; i < mFragments.size(); i++)
	    {
		    outputBuffer.SubCopy(mFragments[i].Pointer(), mFragments[i].Size(), offset); 
		    offset += mFragments[i].Size();
	    }
    }
}

DWORD CFrame::Time()
{
	if (Completed())
	{
		
		double frameTime = (mEndTime.QuadPart - mStartTime.QuadPart) * 1000.0 / mTimerFrequency.QuadPart;
		return (frameTime);
	}
	else
	{
		return (0);
	}
}
