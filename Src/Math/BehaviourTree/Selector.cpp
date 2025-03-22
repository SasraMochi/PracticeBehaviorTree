#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

NodeResult Selector::Run()
{
	Node::Run();

	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		NodeResult result = NodeResult::None;
		if (result != NodeResult::Running) {
			result = node.Run();
		}

		// �ǂꂩ��ł�������Ԃ��Ă�����ێ�
		if (result == NodeResult::Success)
			selector_result = result;
	}

	return selector_result;
}
