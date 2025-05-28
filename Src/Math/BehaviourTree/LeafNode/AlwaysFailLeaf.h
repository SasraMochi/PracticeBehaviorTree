#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 必ず失敗を返すデバッグ用葉ノード
/// </summary>
class AlwaysFailLeaf : public LeafNodeBase {
public:
	explicit AlwaysFailLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~AlwaysFailLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Fail;
	}
};