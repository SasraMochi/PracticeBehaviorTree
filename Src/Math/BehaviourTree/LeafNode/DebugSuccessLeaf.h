#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 必ず失敗を返すデバッグ用葉ノード
/// </summary>
class DebugSuccessLeaf : public LeafNodeBase {
public:
	explicit DebugSuccessLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~DebugSuccessLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Success;
	}
};