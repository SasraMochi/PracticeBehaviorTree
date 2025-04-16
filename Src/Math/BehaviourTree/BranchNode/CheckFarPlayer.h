#pragma once

#include "Math/BehaviourTree/ConditionalBranch/ConditionalBranch.h"

class CheckFarPlayer : public ConditionalBranch {
public:
	CheckFarPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance);

	~CheckFarPlayer();

public:
	NodeResult tick() override;

private:
	const float mMaxDistance = 5;
};