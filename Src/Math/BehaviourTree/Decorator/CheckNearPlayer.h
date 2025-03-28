#pragma once

#include "Decorator.h"

class CheckNearPlayer : public Decorator {
public:
	CheckNearPlayer(BlackBoard* black_board, INode* child_node, const float max_distance);

	~CheckNearPlayer();

public:
	NodeResult tick() override;

private:
	const float mMaxDistance = 5;
};