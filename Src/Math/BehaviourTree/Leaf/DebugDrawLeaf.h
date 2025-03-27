#pragma once

#include <string>
#include "Math/BehaviourTree/INode.h"

class DebugDrawLeaf : public INode {
public:
	DebugDrawLeaf(BlackBoard* black_board, int text);

	~DebugDrawLeaf();

	virtual NodeResult Run() override;

private:
	int mText;
};