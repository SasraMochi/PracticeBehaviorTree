#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(INode* node)
{
	SetNode(node);
}

Inverter::~Inverter()
{
}

NodeResult Inverter::Run()
{
	CheckFirstRun();

	// ���ʂ��o��܂ŉ񂵑�����
	NodeResult result = NodeResult::None;
	do {
		result = mChildNode->Run();
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
	mNodeResult = NodeResult::None;
	return mNodeResult;
}
