#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

NodeResult Selector::Run()
{
	CheckFirstRun();

	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		// �m�[�h�����������s��Ԃ��܂�Run��������
		NodeResult result = NodeResult::None;
		do {
			result = node->Run();
		} while (result == NodeResult::Running);

		// �����ɐ�����Ԃ�
		if (result == NodeResult::Success) {
			mNodeResult = NodeResult::Success;
			return mNodeResult;
		}
	}

	mNodeResult = NodeResult::Fail;
	return mNodeResult;
}
