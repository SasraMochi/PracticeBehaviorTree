#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// プレイヤーから逃げる葉ノード
/// </summary>
class EscapeFromPlayerLeaf : public LeafNodeBase {
public:
	explicit EscapeFromPlayerLeaf(BlackBoard* black_board);

	~EscapeFromPlayerLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};