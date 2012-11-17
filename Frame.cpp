
#include "Frame.h"

CFrame::CFrame()
:
	mNumberOfFragments(0),
    mFrameSizeInBytes(0)
{
	Reset(1);
}

CFrame::~CFrame()
{

}

void CFrame::Reset(const int numberOfFragments)
{
	mNumberOfFragments = numberOfFragments;

	mReceivedFragments.reserve(mNumberOfFragments);
	mFragments.reserve(mNumberOfFragments);

	mFrameSizeInBytes = 0;
}

void CFrame::AddFragment(const char* pBuffer,
						 const int   length,
					     const int   fragmentNumber)
{

}

bool CFrame::Completed() const
{
	return (false);
}

int  CFrame::SizeInBytes() const
{
	return (mFrameSizeInBytes);
}

int  CFrame::Combine(const char* pBuffer)
{
	return (0);
}