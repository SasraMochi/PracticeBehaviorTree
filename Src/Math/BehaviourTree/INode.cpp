#include "INode.h"

void INode::CheckFirstRun()
{
	if (mNodeResult == NodeResult::Running) return;

	SetRunnning();
}

INode::INode(BlackBoard* black_board)
	: mpBlackBoard(black_board)
{
}

void INode::Reset()
{
	mNodeResult = NodeResult::None;
}

void INode::SetRunnning()
{
	mNodeResult = NodeResult::Running;
}
