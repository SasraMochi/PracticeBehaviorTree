#pragma once

#include "Node.h"

class Decorator : public Node{
public:
	virtual void SetNode(Node node);

protected:
	Node mChildNode;
};