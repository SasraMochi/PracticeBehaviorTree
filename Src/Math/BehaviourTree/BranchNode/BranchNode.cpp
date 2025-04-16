#include "BranchNode.h"

BranchNode::BranchNode(BlackBoard* black_board, INode* true_node, INode* false_node)
	: NodeBase(black_board)
	, mpTrueNode(true_node)
	, mpFalseNode(false_node)
{
}

BranchNode::~BranchNode()
{
	if (mpTrueNode) {
		delete mpTrueNode;
		mpTrueNode = nullptr;
	}
	if (mpFalseNode) {
		delete mpFalseNode;
		mpFalseNode = nullptr;
	}
}

void BranchNode::reset()
{
	mpTrueNode->reset();
	mpFalseNode->reset();
}
