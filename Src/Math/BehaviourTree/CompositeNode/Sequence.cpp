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
		// ����Sequence�Ɍ����ăm�[�h�ԍ���i�߂�
		node_increment();
		return;
	}

	// �������s���Ԃ��ꂽ��m�[�h�I��
	if (result == NodeResult::Fail) {
		finalize();
	}

	mNodeResult = result;
}

const int Sequence::get_next_index() const
{
	return mRunningNodeIndex + 1;
}
