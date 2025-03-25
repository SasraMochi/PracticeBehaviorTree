#pragma once

#include "INode.h"

class DebugFailLeaf : public INode {
public:
	virtual NodeResult Run() override;
};