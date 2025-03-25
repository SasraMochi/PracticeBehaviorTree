#pragma once

#include "INode.h"

class DebugSuccessLeaf : public INode{
public:
	virtual NodeResult Run() override;
};