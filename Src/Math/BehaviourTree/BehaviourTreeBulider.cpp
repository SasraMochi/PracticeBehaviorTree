#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Math/BehaviourTree/Composite/Selector.h"
#include "Math/BehaviourTree/Composite/Sequence.h"
#include "Math/BehaviourTree/Decorator/Inverter.h"
#include "Math/BehaviourTree/Decorator/CheckNearPlayer.h"
#include "Leaf/ChasePlayerLeaf.h"

#include "Leaf/DebugDrawLeaf.h"


INode* BehaviourTreeBuilder::BuildAttackerTree(BlackBoard* blackboard)
{
	auto selector = new Selector(blackboard);
	selector->add_node(new CheckNearPlayer(blackboard, new ChasePlayerLeaf(blackboard), 10.f));
	return selector;
}
