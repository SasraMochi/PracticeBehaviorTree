#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Math/BehaviourTree/Composite/Selector.h"
#include "Math/BehaviourTree/Composite/Sequence.h"
#include "Math/BehaviourTree/Decorator/Inverter.h"
#include "Math/BehaviourTree/ConditionalBranch/CheckNearPlayer.h"
#include "Math/BehaviourTree/ConditionalBranch/CheckFarPlayer.h"
#include "Math/BehaviourTree//Leaf/WaitLeaf.h"
#include "Math/BehaviourTree//Leaf/ChasePlayerLeaf.h"
#include "Math/BehaviourTree//Leaf/EscapePlayerLeaf.h"
#include "Math/BehaviourTree//Leaf/CircleAttackLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugFailLeaf.h"

#include "Leaf/DebugDrawLeaf.h"


INode* BehaviourTreeBuilder::BuildAttackerTree(BlackBoard* blackboard)
{
	auto chase_selector = new Selector(blackboard);
	auto chase_inverter = new Inverter(blackboard, new ChasePlayerLeaf(blackboard));
	chase_selector->add_node(new CheckNearPlayer(blackboard, new DebugSuccessLeaf(blackboard), chase_inverter, 100.f));

	auto root_sequence = new Sequence(blackboard);
	root_sequence->add_node(chase_selector);
	root_sequence->add_node(new CircleAttackLeaf(blackboard));
	root_sequence->add_node(new WaitLeaf(blackboard, 60.f));
	return root_sequence;
}