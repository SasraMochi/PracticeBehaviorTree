#include "Sequence.h"

Sequence::Sequence(BlackBoard* black_board)
	: CompositeNodeBase(black_board)
{
	
}

Sequence::~Sequence()
{
}

void Sequence::tick()
{
	mChildNodes[mRunningNodeIndex]->tick();
	auto result = mChildNodes[mRunningNodeIndex]->get_node_result();

	if (result == NodeResult::Success) {
		// 次回Sequenceに向けてノード番号を進める
		node_increment();
		return;
	}

	// もし失敗が返されたらノード終了
	if (result == NodeResult::Fail) {
		finalize();
	}

	mNodeResult = result;
}

const int Sequence::get_next_index() const
{
	return mRunningNodeIndex + 1;
}
