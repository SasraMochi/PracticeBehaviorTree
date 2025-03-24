#include "INode.h"

void INode::CheckFirstRun()
{
	if (mNodeResult != NodeResult::None) return;

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
