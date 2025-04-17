#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// プレイヤーを追いかける葉ノード
/// </summary>
class ChasePlayerLeaf : public LeafNodeBase {
public:
	explicit ChasePlayerLeaf(BlackBoard* black_board);

	~ChasePlayerLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};