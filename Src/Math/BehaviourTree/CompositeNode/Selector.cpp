#include "Selector.h"

Selector::Selector(BlackBoard* black_board)
	: CompositeNodeBase(black_board)
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

void Selector::init()
{
	CompositeNodeBase::init();
	// 最初のノードを初期化
	if (mChildNodes.size() > 0) {
		mChildNodes[mRunningNodeIndex]->init();
	}
	else {
		mNodeResult = NodeResult::Fail;
	}
}

void Selector::tick()
{
	mChildNodes[mRunningNodeIndex]->tick();
	auto result = mChildNodes[mRunningNodeIndex]->get_node_result();

	if (result == NodeResult::Success) {
		reset();
	}
	else if (result == NodeResult::Fail) {
		// 次回Sequenceに向けてノード番号をリセット
		node_increment();
	}

	mNodeResult = result;
}

void Selector::node_increment()
{
	mRunningNodeIndex++;
	if (mRunningNodeIndex > mChildNodes.size() - 1) {
		reset();
	}
	else {
		mChildNodes[mRunningNodeIndex]->reset();
	}
}
