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
	virtual NodeResult tick() = 0;

	// ���Z�b�g
	virtual void reset();

protected:
	// �����Ăяo�������`�F�b�N����
	void check_first_run();

private:
	void set_running_();

protected:
	BlackBoard* mpBlackBoard = nullptr;

	NodeResult mNodeResult = NodeResult::None;
};