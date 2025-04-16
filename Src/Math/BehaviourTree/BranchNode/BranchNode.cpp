#include "BranchNode.h"

BranchNode::BranchNode(BlackBoard* black_board, INode* true_node, INode* false_node)
	: NodeBase(black_board)
{
	mpBranchNodes[0] = true_node;
	mpBranchNodes[1] = false_node;
}

BranchNode::~BranchNode()
{
	// ブランチノードの配列を解放
	for (int i = 0; i < 2; ++i) {
		if (mpBranchNodes[i] != nullptr) {
			delete mpBranchNodes[i];
			mpBranchNodes[i] = nullptr;
		}
	}
}

void BranchNode::init()
{
	NodeBase::init();

	if (is_condition) mSatisfyIndex = 0;
	else mSatisfyIndex = 1;

	mpBranchNodes[mSatisfyIndex]->init();
}

void BranchNode::tick()
{
	mpBranchNodes[mSatisfyIndex]->tick();
	mNodeResult = mpBranchNodes[mSatisfyIndex]->get_node_result();
}

void BranchNode::finalize()
{
	NodeBase::finalize();
	mpBranchNodes[mSatisfyIndex]->finalize();
	mSatisfyIndex = -1;
}
