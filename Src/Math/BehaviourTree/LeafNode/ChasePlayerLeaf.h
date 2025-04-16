#pragma once

#include "Math/BehaviourTree/INode.h"

class ChasePlayerLeaf : public INode {
public:
	ChasePlayerLeaf(BlackBoard* black_board);

	~ChasePlayerLeaf();

	NodeResult tick() override;
};