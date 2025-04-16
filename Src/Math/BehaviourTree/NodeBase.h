#pragma once

#include "Math/BehaviourTree/INode.h"

class BlackBoard;

// �e�m�[�h�̊��N���X
class NodeBase : INode {
protected:
	explicit NodeBase(BlackBoard* black_board) : mpBlackBoard{ black_board } {}
	virtual ~NodeBase() = default;

private:
	NodeResult mNodeResult = NodeResult::Idle; // �m�[�h�̏��
	BlackBoard* mpBlackBoard = nullptr; // �u���b�N�{�[�h
};