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

void INode::SetOwner(Actor* actor)
{
	mpOwner = actor;
}

void INode::SetRunnning()
{
	mNodeResult = NodeResult::Running;
}
