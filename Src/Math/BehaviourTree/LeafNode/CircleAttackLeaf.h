#pragma once

#include "Math/BehaviourTree/INode.h"

class CircleAttackLeaf : public INode {
public:
	CircleAttackLeaf(BlackBoard* black_board);
	~CircleAttackLeaf();

	NodeResult tick() override;
};