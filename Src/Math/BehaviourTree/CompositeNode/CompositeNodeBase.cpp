#include "CompositeNodeBase.h"

CompositeNodeBase::~CompositeNodeBase()
{
	for (auto node : mChildNodes) {
		delete node;
	}
	mChildNodes.clear();
}

void CompositeNodeBase::init()
{
	NodeBase::init();
	mRunningNodeIndex = 0;

	// Å‰‚Ìƒm[ƒh‚ð‰Šú‰»
	if (mChildNodes.size() > 0) {
		mChildNodes[mRunningNodeIndex]->init();
	}
	else {
		mNodeResult = NodeResult::Fail;
	}
}

void CompositeNodeBase::finalize()
{
	NodeBase::finalize();

	// Å‰‚Ìƒm[ƒh‚ð‰Šú‰»
	mRunningNodeIndex = 0;
	mChildNodes[mRunningNodeIndex]->init();
}

void CompositeNodeBase::add_node(INode* node)
{
	mChildNodes.push_back(node);
}