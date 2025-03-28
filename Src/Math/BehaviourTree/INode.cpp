#include "INode.h"

void INode::check_first_run()
{
	if (mNodeResult == NodeResult::Running) return;

	set_running_();
}

INode::INode(BlackBoard* black_board)
	: mpBlackBoard(black_board)
{
}

void INode::reset()
{
	mNodeResult = NodeResult::None;
}

void INode::set_running_()
{
	mNodeResult = NodeResult::Running;
}
