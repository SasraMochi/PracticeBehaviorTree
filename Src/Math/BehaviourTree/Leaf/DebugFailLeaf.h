#pragma once

#include "Math/BehaviourTree/INode.h"

class DebugFailLeaf : public INode {
public:
	DebugFailLeaf(BlackBoard* black_board) : INode(black_board) {}

	virtual NodeResult Run() override;
};