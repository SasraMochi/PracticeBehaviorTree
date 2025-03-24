#pragma once

#include "INode.h"

class Decorator : public INode{
public:
	virtual void SetNode(INode* node);

protected:
	INode* mChildNode;
};