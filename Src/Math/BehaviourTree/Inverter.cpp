#include "Inverter.h"

Inverter::Inverter()
{
}

Inverter::~Inverter()
{
}

NodeResult Inverter::Run()
{
	CheckFirstRun();

	NodeResult result = NodeResult::None;

	// ���������s��Ԃ��܂Ŏ��s
	// do�Ő�Ɏ��s���Ă���
	do {
		result = mChildNode->Run();
	} while (result == NodeResult::Running);

	if (result == NodeResult::Success) {
		return NodeResult::Fail;
	}
	else if (result == NodeResult::Fail) {
		return NodeResult::Success;
	}

	// ���ʂ͂����܂Ŏ��s����邱�Ƃ͂Ȃ�
	// TODO ��X�A�T�[�g�Ă�
	return NodeResult::None;
}
