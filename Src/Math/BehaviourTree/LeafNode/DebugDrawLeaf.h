#pragma once

#include <string>
#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 文字のデバッグ描画を行う葉ノード
/// </summary>
class DebugDrawLeaf : public LeafNodeBase {
public:
	explicit DebugDrawLeaf(BlackBoard* black_board, int text);

	~DebugDrawLeaf();

	void tick() override;

	NodeResult get_node_result() const override;

private:
	int mText;
};