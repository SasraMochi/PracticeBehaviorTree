#pragma once

#include <vector>
#include "INode.h"

class Composite : public INode {
public:
	Composite(BlackBoard* black_board) : INode(black_board) {
	};

	void add_node(INode* node);

protected:
	std::vector<INode*> mChildNodes;
};