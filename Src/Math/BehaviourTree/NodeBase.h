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

private:
	NodeResult mNodeResult = NodeResult::Idle; // �m�[�h�̏��
	BlackBoard* mpBlackBoard = nullptr; // �u���b�N�{�[�h
};