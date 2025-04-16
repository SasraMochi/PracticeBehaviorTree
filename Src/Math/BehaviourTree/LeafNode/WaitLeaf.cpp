#include "WaitLeaf.h"

WaitLeaf::WaitLeaf(BlackBoard* black_board, const float wait_time)
	: INode(black_board)
	, mWaitTime(wait_time)
	, mWaitCount(wait_time)
{
}

WaitLeaf::~WaitLeaf()
{
}

NodeResult WaitLeaf::tick()
{
	if (mWaitCount <= 0.f) {
		return NodeResult::Success;
	}

	mWaitCount -= 1.f;

	return NodeResult::Running;
}

void WaitLeaf::reset()
{
	INode::reset();
	mWaitCount = mWaitTime;
}
