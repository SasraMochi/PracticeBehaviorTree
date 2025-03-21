#pragma once

#include <vector>
#include "Node.h"

class Composite : public Node {
public:
	virtual void AddNode(Node node);

protected:
	std::vector<Node> mChildNodes;
};