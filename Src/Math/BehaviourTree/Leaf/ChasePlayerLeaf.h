#pragma once

#include "Math/BehaviourTree/INode.h"

class Player;

class ChasePlayerLeaf : public INode {
public:
	ChasePlayerLeaf(BlackBoard* black_board);

	~ChasePlayerLeaf();

	NodeResult tick() override;

private:
	Player* mpPlayer = nullptr;
};