#include "INode.h"

void INode::CheckFirstRun()
{
	if (mNodeResult == NodeResult::Running) return;

	SetRunnning();
}

void INode::Reset()
{
	mNodeResult = NodeResult::None;
}

void INode::SetRunnning()
{
	mNodeResult = NodeResult::Running;
}
