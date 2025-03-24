#include "Composite.h"

void Composite::AddNode(INode* node)
{
	mChildNodes.push_back(node);
}
