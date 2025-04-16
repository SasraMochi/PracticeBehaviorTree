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
		// ����Sequence�Ɍ����ăm�[�h�ԍ���i�߂�
		node_increment();
		return;
	}

	// �����������Ԃ��ꂽ��m�[�h�I��
	if (result == NodeResult::Success) {
		finalize();
	}

	mNodeResult = result;
}

const int Selector::get_next_index() const
{
	return mRunningNodeIndex + 1;
}