#include "Selector.h"

Selector::Selector(BlackBoard* black_board)
	: CompositeNodeBase(black_board)
{

}

Selector::~Selector()
{
}

void Selector::tick()
{
	mChildNodes[mRunningNodeIndex]->tick();
	auto result = mChildNodes[mRunningNodeIndex]->get_node_result();

	if (result == NodeResult::Fail) {
		// 次回Sequenceに向けてノード番号を進める
		node_increment();
		return;
	}

	// もし成功が返されたらノード終了
	if (result == NodeResult::Success) {
		finalize();
	}

	mNodeResult = result;
}

const int Selector::get_next_index() const
{
	return mRunningNodeIndex + 1;
}