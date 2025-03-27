#pragma once
#include "NodeResult.h"

class BlackBoard;

class INode {
public:
	// �R���X�g���N�^
	explicit INode(BlackBoard* black_board);

	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ����
	virtual NodeResult Run() = 0;

	// ���Z�b�g
	virtual void Reset();

protected:
	// �����Ăяo�������`�F�b�N����
	void CheckFirstRun();

private:
	void SetRunnning();

protected:
	BlackBoard* mpBlackBoard = nullptr;

	NodeResult mNodeResult = NodeResult::None;
};