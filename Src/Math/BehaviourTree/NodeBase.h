#pragma once

#include "Math/BehaviourTree/INode.h"

class BlackBoard;

/// <summary>
/// �e�m�[�h���p��������N���X
/// </summary>
class NodeBase : public INode {
protected:
	explicit NodeBase(BlackBoard* black_board) : mpBlackBoard{ black_board } {}
	virtual ~NodeBase() = default;

	NodeResult get_node_result() const {
		return mNodeResult;
	}

	virtual void init() override {
		mNodeResult = NodeResult::Running;
	}

	virtual void finalize() override {
		mNodeResult = NodeResult::Idle;
	}

	NodeResult mNodeResult = NodeResult::Idle; // �m�[�h�̏��
	BlackBoard* mpBlackBoard = nullptr; // �u���b�N�{�[�h
};