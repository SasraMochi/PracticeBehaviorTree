#pragma once

#include "Math/BehaviourTree/INode.h"

class DebugSuccessLeaf : public INode{
public:
	virtual NodeResult Run() override;
};