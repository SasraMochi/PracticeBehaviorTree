#include "ConditionalBranch.h"

ConditionalBranch::ConditionalBranch(BlackBoard* black_board, INode* true_node, INode* false_node)
	: INode(black_board)
	, mpTrueNode(true_node)
	, mpFalseNode(false_node)
{
}

ConditionalBranch::~ConditionalBranch()
{
}

void ConditionalBranch::reset()
{
	mpTrueNode->reset();
	mpFalseNode->reset();
}
