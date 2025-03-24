#pragma once

#include <vector>
#include "INode.h"

class Composite : public INode {
public:
	virtual void AddNode(INode* node);

protected:
	std::vector<INode*> mChildNodes;
};