#include "Selector.h"

Selector::Selector(BlackBoard* black_board)
	: Composite(black_board)
{
	
}

Selector::~Selector()
{
}

void Selector::reset()
{
	INode::reset();
	mRunningNodeIndex = 0;
	mChildNodes[mRunningNodeIndex]->reset();
}

NodeResult Selector::tick()
{
	check_first_run();

	mNodeResult = mChildNodes[mRunningNodeIndex]->tick();

	if (mNodeResult == NodeResult::Success) {
		reset();
		mNodeResult = NodeResult::Success;
	}
	else if (mNodeResult == NodeResult::Fail) {
		// ����Sequence�Ɍ����ăm�[�h�ԍ������Z�b�g
		node_increment();
		mNodeResult = NodeResult::Running;
	}

	return mNodeResult;
}

void Selector::node_increment()
{
	mRunningNodeIndex++;
	if (mRunningNodeIndex > mChildNodes.size() - 1) {
		reset();
		return;
	}

	mChildNodes[mRunningNodeIndex]->reset();
}
