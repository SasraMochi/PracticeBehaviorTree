#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 必ず成功を返す葉ノード
/// </summary>
class AlwaysSuccessLeaf : public LeafNodeBase {
public:
	explicit AlwaysSuccessLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~AlwaysSuccessLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Success;
	}
};