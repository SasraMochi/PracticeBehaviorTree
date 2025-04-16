#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(BlackBoard* black_board, INode* child_node)
	: DecoratorNodeBase(black_board)
{
	set_node(child_node);
}

Inverter::~Inverter()
{
}

NodeResult Inverter::tick()
{
	check_first_run();

	// ���ʂ��o��܂ŉ񂵑�����
	NodeResult result = NodeResult::Idle;
	do {
		result = mChildNode->tick();
	} while (result == NodeResult::Running);

	// ���ʂ𔽓]������
	if (result == NodeResult::Success) {
		mNodeResult = NodeResult::Fail;
		return mNodeResult;
	}
	else if (result == NodeResult::Fail) {
		mNodeResult = NodeResult::Success;
		return mNodeResult;
	}

	// ���ʂ͂����܂Ŏ��s����邱�Ƃ͂Ȃ�
	// TODO ��X�A�T�[�g�Ă�
	assert(!"���ʂ��s���ł�");
	mNodeResult = NodeResult::Idle;
	return mNodeResult;
}
