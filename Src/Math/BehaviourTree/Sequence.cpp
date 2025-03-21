#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::~Sequence()
{
}

NodeResult Sequence::Run()
{
	for (auto& node : mChildNodes)
	{
		NodeResult result = NodeResult::None;
		if (result != NodeResult::Running) {
			result = node.Run();
			
			// ���s���Ɏ��s��Ԃ����玸�s��Ԃ�
			if (result == NodeResult::Fail) {
				return result;
			}
		}
	}

	return NodeResult::Success;
}
