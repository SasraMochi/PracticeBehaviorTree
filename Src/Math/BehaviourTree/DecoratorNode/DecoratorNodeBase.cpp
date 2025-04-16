#include "Decorator.h"

DecoratorNodeBase::~DecoratorNodeBase()
{
	if (mChildNode) {
		delete mChildNode;
		mChildNode = nullptr;
	}
}

void DecoratorNodeBase::set_node(INode* node)
{
	mChildNode = node;
}
