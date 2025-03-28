#include "Composite.h"

void Composite::add_node(INode* node)
{
	mChildNodes.push_back(node);
}
