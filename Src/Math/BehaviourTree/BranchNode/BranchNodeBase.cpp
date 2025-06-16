#include "BranchNodeBase.h"

BranchNodeBase::BranchNodeBase(BlackBoard* black_board, INode* true_node, INode* false_node)
	: NodeBase(black_board)
{
	mpBranchNodes[0] = true_node;
	mpBranchNodes[1] = false_node;
}

BranchNodeBase::~BranchNodeBase()
{
	// ブランチノードの配列を解放
	for (int i = 0; i < 2; ++i) {
		if (mpBranchNodes[i] != nullptr) {
			delete mpBranchNodes[i];
			mpBranchNodes[i] = nullptr;
		}
	}
}

void BranchNodeBase::init()
{
	NodeBase::init();

	if (is_condition())
	{
		mSatisfyIndex = 0;
	}
	else
	{
		mSatisfyIndex = 1;
	}

	mpBranchNodes[mSatisfyIndex]->init();
}

void BranchNodeBase::tick()
{
	mpBranchNodes[mSatisfyIndex]->tick();
	mNodeResult = mpBranchNodes[mSatisfyIndex]->get_node_result();
}

void BranchNodeBase::finalize()
{
	NodeBase::finalize();
	mpBranchNodes[mSatisfyIndex]->finalize();
	mSatisfyIndex = -1;
}

int BranchNodeBase::get_running_node_id() const
{
	return mpBranchNodes[mSatisfyIndex]->get_running_node_id();
}
