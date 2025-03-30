#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Math/BehaviourTree/Composite/Selector.h"
#include "Math/BehaviourTree/Composite/Sequence.h"
#include "Math/BehaviourTree/Decorator/Inverter.h"
#include "Math/BehaviourTree/Decorator/CheckNearPlayer.h"
#include "Math/BehaviourTree/Decorator/CheckFarPlayer.h"
#include "Leaf/ChasePlayerLeaf.h"
#include "Leaf/EscapePlayerLeaf.h"

#include "Leaf/DebugDrawLeaf.h"


INode* BehaviourTreeBuilder::BuildAttackerTree(BlackBoard* blackboard)
{
	auto selector = new Selector(blackboard);
	selector->add_node(new CheckFarPlayer(blackboard, new ChasePlayerLeaf(blackboard), 100.f));
	selector->add_node(new EscapePlayerLeaf(blackboard));
	return selector;
}