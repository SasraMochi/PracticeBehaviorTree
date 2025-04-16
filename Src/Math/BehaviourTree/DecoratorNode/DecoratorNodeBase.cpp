#include "Decorator.h"

Decorator::~Decorator()
{
	if (mChildNode) {
		delete mChildNode;
		mChildNode = nullptr;
	}
}

void Decorator::set_node(INode* node)
{
	mChildNode = node;
}
