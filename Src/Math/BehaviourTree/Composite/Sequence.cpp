#include "Sequence.h"

Sequence::Sequence(BlackBoard* black_board)
	: Composite(black_board)
{
	
}

Sequence::~Sequence()
{
}

void Sequence::reset()
{
	INode::reset();
	mRunningNodeIndex = 0;
	mChildNodes[mRunningNodeIndex]->reset();
}

NodeResult Sequence::tick()
{
	check_first_run();

	mNodeResult = mChildNodes[mRunningNodeIndex]->tick();

	if (mNodeResult == NodeResult::Fail) {
		// 次回Sequenceに向けてノード番号をリセット
		reset();
		mNodeResult = NodeResult::Fail;
	}
	else if (mNodeResult == NodeResult::Success) {
		node_increment();

		mNodeResult = NodeResult::Running;
	}

	return mNodeResult;
}

void Sequence::node_increment()
{
	mRunningNodeIndex++;
	if (mRunningNodeIndex > mChildNodes.size() - 1) {
		reset();
	}

	mChildNodes[mRunningNodeIndex]->reset();
}
