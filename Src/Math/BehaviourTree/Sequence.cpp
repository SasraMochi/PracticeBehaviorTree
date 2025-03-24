#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::~Sequence()
{
}

NodeResult Sequence::Run()
{
	CheckFirstRun();

	for (auto& node : mChildNodes)
	{
		// �m�[�h�����������s��Ԃ��܂�Run��������
		NodeResult result = NodeResult::None;
		do {
			node->CheckFirstRun();
			result = node->Run();
		} while(result == NodeResult::Running);

		// ���s���Ɏ��s��Ԃ����玸�s��Ԃ�
		if (result == NodeResult::Fail) {
			return result;
		}
	}

	return NodeResult::Success;
}
