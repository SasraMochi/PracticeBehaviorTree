#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

NodeResult Selector::Run()
{
	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		// �m�[�h�����������s��Ԃ��܂�Run��������
		NodeResult result = NodeResult::None;
		do {
			node->CheckFirstRun();
			result = node->Run();
		} while (result == NodeResult::Running);

		// �ǂꂩ��ł�������Ԃ��Ă��瑦���ɐ�����Ԃ�
		if (result == NodeResult::Success)
			return NodeResult::Success;
	}

	return NodeResult::Fail;
}
