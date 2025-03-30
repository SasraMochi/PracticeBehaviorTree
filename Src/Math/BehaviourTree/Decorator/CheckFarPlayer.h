#pragma once

#include "Decorator.h"

class CheckFarPlayer : public Decorator {
public:
	CheckFarPlayer(BlackBoard* black_board, INode* child_node, const float max_distance);

	~CheckFarPlayer();

public:
	NodeResult tick() override;

private:
	const float mMaxDistance = 5;
};