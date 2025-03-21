#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

NodeResult Node::Run()
{
	if (mNodeResult == NodeResult::None)
		mNodeResult = NodeResult::Running;

	return mNodeResult;
}
