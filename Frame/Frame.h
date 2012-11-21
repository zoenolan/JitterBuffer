#ifndef _FRAME_H
#define _FRAME_H

#include <vector>

#include "../LazyBuffer/LazyBuffer.h"

class CFrame
{
public:
	CFrame();

	/*
	Reset the frame meta data
	@param numberOfFragments - will start at zero for the call
	*/
	void Reset(const int numberOfFragments);

	/*
	Add one fragment to the Frame
	@param pBuffer - pointer to the fragments data
	@param length  - length of the frgment
	@param fragmentNumber - specifies what position this fragment is within the given
	frame - the first fragment number in each frame is number zero
	*/
	void AddFragment(const char* pBuffer,
					 const int   length,
					 const int   fragmentNumber);

	/*
	Have all the fragments for the frame been recieved
	*/
	bool Completed() const;

	/*
	Copy the completed frame into the provided buffer
	@param outputBuffer - Buffer to use for the completed frame
	*/
	void Combine(CLazyBuffer& outputBuffer);

private:
	int					     mFragmentsRemaining;

	std::vector<bool>        mSeenFragment;
	std::vector<CLazyBuffer> mFragments;

	int					     mFrameSizeInBytes;
};

#endif // _FRAME_H
