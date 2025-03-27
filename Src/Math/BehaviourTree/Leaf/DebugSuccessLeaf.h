#pragma once

#include "Math/BehaviourTree/INode.h"

class DebugSuccessLeaf : public INode{
public:
	DebugSuccessLeaf(BlackBoard* black_board) : INode(black_board) {}

	virtual NodeResult Run() override;
};