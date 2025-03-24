#pragma once

#include <string>
#include "Math/BehaviourTree/INode.h"

class DebugDrawLeaf : public INode {
public:
	DebugDrawLeaf(std::string text);

	~DebugDrawLeaf();

	virtual NodeResult Run() override;

private:
	std::string mText;
};