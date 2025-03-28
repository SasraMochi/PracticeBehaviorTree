#pragma once

#include "Math/BehaviourTree/INode.h"

class Decorator : public INode{
public:
	Decorator(BlackBoard* black_board) : INode(black_board) {}

	void set_node(INode* node);

protected:
	INode* mChildNode = nullptr;
};