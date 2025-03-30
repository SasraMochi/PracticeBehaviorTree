#pragma once

#include "Math/BehaviourTree/INode.h"

class EscapePlayerLeaf : public INode {
public:
	EscapePlayerLeaf(BlackBoard* black_board);

	~EscapePlayerLeaf();

	NodeResult tick() override;
};