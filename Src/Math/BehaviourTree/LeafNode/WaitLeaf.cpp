#include "WaitLeaf.h"

WaitLeaf::WaitLeaf(BlackBoard* black_board, const float wait_time)
	: LeafNodeBase(black_board)
	, mWaitTime(wait_time)
	, mWaitCount(wait_time)
{
}

WaitLeaf::~WaitLeaf()
{
}

void WaitLeaf::tick()
{
	if (mWaitCount <= 0.f) {
		mNodeResult = NodeResult::Success;
		return;
	}

	mWaitCount -= 1.f;
}

void WaitLeaf::finalize()
{
	LeafNodeBase::finalize();
	mWaitCount = mWaitTime;
}
