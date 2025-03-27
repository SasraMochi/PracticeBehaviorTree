#pragma once

#include "INode.h"

class Decorator : public INode{
public:
	Decorator(BlackBoard* black_board) : INode(black_board) {}

	void SetNode(INode* node);

protected:
	INode* mChildNode = nullptr;
};