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

	// Å‰‚Ìƒm[ƒh‚ğ‰Šú‰»
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

	// Å‰‚Ìƒm[ƒh‚ğ‰Šú‰»
	mRunningNodeIndex = 0;
	mChildNodes[mRunningNodeIndex]->init();
}

void CompositeNodeBase::add_node(INode* node)
{
	mChildNodes.push_back(node);
}

int CompositeNodeBase::get_running_node_id() const
{
	// Œ»İ“®‚©‚µ‚Ä‚¢‚éƒm[ƒh‚ÌID‚ğ•Ô‚·
	return mChildNodes[mRunningNodeIndex]->get_running_node_id();
}
