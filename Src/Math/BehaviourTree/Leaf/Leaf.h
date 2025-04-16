#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// 葉ノードの基底クラス
/// </summary>
class Leaf : public NodeBase {
protected:
	explicit Leaf(BlackBoard* black_board) : NodeBase{ black_board } {}
	virtual ~Leaf() = default;
};