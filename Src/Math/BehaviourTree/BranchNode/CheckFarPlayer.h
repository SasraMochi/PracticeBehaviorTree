#pragma once

#include "Math/BehaviourTree/BranchNode/BranchNodeBase.h"

class CheckFarPlayer : public BranchNodeBase {
public:
	explicit CheckFarPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance);

	~CheckFarPlayer();

private:
	const bool is_condition() override;

private:
	const float mMaxDistance = 5;
};