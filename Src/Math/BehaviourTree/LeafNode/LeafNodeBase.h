#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// 葉ノードの基底クラス
/// </summary>
class LeafNodeBase : public NodeBase {
protected:
	explicit LeafNodeBase(BlackBoard* black_board) : NodeBase{ black_board } {}
	virtual ~LeafNodeBase() = default;
};