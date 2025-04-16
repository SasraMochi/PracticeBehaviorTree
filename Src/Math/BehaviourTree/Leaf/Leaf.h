#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �t�m�[�h�̊��N���X
/// </summary>
class Leaf : public NodeBase {
protected:
	explicit Leaf(BlackBoard* black_board) : NodeBase{ black_board } {}
	virtual ~Leaf() = default;
};