#pragma once

#include "Math/BehaviourTree/BranchNode/BranchNode.h"

class CheckNearPlayer : public BranchNode {
public:
	explicit CheckNearPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance);

	~CheckNearPlayer();

private:
	const bool is_condition() override;

private:
	const float mMaxDistance = 5;
};