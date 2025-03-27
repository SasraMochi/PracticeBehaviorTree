#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Selector.h"
#include "Sequence.h"
#include "Inverter.h"
#include "Leaf/ChasePlayerLeaf.h"

#include "Leaf/DebugDrawLeaf.h"


INode* BehaviourTreeBuilder::BuildAttackerTree(BlackBoard* blackboard)
{
	auto selector = new Selector(blackboard);
	selector->AddNode(new ChasePlayerLeaf(blackboard));
	return selector;
}
