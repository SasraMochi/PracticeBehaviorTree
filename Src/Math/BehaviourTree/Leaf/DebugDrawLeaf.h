#pragma once

#include <string>
#include "Math/BehaviourTree/INode.h"

class DebugDrawLeaf : public INode {
public:
	DebugDrawLeaf(BlackBoard* black_board, int text);

	~DebugDrawLeaf();

	virtual NodeResult tick() override;

private:
	int mText;
};