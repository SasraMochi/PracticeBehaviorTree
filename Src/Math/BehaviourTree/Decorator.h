#pragma once

#include "INode.h"

class Decorator : public INode{
public:
	void SetNode(INode* node);

protected:
	INode* mChildNode;
};