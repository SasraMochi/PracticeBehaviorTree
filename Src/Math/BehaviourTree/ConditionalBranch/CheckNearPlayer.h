#pragma once

#include "Math/BehaviourTree/ConditionalBranch/ConditionalBranch.h"

class CheckNearPlayer : public ConditionalBranch {
public:
	CheckNearPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance);

	~CheckNearPlayer();

public:
	NodeResult tick() override;

private:
	const float mMaxDistance = 5;
};