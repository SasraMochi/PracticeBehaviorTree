#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 円形攻撃を行う葉ノード
/// </summary>
class CircleAttackLeaf : public LeafNodeBase {
public:
	explicit CircleAttackLeaf(BlackBoard* black_board);
	~CircleAttackLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};