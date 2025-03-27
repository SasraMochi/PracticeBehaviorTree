#include "Sequence.h"

Sequence::Sequence(BlackBoard* black_board)
	: Composite(black_board)
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
			result = node->Run();
		} while(result == NodeResult::Running);

		// ���s���Ɏ��s��Ԃ����玸�s��Ԃ�
		if (result == NodeResult::Fail) {
			mNodeResult = NodeResult::Fail;
			return mNodeResult;
		}
	}

	mNodeResult = NodeResult::Success;
	return NodeResult::Success;
}
