#pragma once

#include "Math/BehaviourTree/INode.h"

class DebugFailLeaf : public INode {
public:
	virtual NodeResult Run() override;
};