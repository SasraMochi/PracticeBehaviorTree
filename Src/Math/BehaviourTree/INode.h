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
	// �t���O�𓮍쒆�ɐ؂�ւ���
	void set_running_();

protected:
	// �Q�Ƃł���u���b�N�{�[�h
	BlackBoard* mpBlackBoard = nullptr;

	// ���
	NodeResult mNodeResult = NodeResult::None;
};