#pragma once

#include "Math/BehaviourTree/INode.h"

class Player;

class ChasePlayerLeaf : public INode {
public:
	ChasePlayerLeaf();

	~ChasePlayerLeaf();

private:
	Player* mpPlayer = nullptr;
};