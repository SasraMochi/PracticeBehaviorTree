#include "Math/BehaviourTree/DecoratorNode/DecoratorNodeBase.h"

DecoratorNodeBase::~DecoratorNodeBase()
{
	if (mChildNode) {
		delete mChildNode;
		mChildNode = nullptr;
	}
}

void DecoratorNodeBase::init()
{
	NodeBase::init();
	mChildNode->init();
}

void DecoratorNodeBase::finalize()
{
	NodeBase::finalize();
	mChildNode->finalize();
}

void DecoratorNodeBase::set_node(INode* node)
{
	mChildNode = node;
}
