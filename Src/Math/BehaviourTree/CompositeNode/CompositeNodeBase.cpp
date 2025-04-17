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

	// 最初のノードを初期化
	if (mChildNodes.size() > 0) {
		mChildNodes[mRunningNodeIndex]->init();
	}
	else {
		mNodeResult = NodeResult::Fail;
	}
}

void CompositeNodeBase::add_node(INode* node)
{
	mChildNodes.push_back(node);
}

void CompositeNodeBase::node_increment()
{
	// 現在のノードの後始末
	mChildNodes[mRunningNodeIndex]->finalize();

	// インデックスを進める
	mRunningNodeIndex = get_next_index();

	// もしすべての子ノードを試しても失敗したら
	if (mRunningNodeIndex > mChildNodes.size() - 1) {
		mNodeResult = NodeResult::Fail;
		init();
		return;
	}

	// 次に回すノードの初期化
	mChildNodes[mRunningNodeIndex]->init();
}
