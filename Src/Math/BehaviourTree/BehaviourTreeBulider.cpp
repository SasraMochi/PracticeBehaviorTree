#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Math/BehaviourTree/CompositeNode/Selector.h"
#include "Math/BehaviourTree/CompositeNode/Sequence.h"
#include "Math/BehaviourTree/DecoratorNode/Inverter.h"
#include "Math/BehaviourTree/BranchNode/CheckNearPlayer.h"
#include "Math/BehaviourTree/BranchNode/CheckFarPlayer.h"
#include "Math/BehaviourTree/LeafNode/WaitLeaf.h"
#include "Math/BehaviourTree/LeafNode/ChasePlayerLeaf.h"
#include "Math/BehaviourTree/LeafNode/EscapeFromPlayerLeaf.h"
#include "Math/BehaviourTree/LeafNode/CircleAttackLeaf.h"
#include "Math/BehaviourTree/LeafNode/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/LeafNode/DebugFailLeaf.h"
#include "Math/BehaviourTree/LeafNode/DebugDrawLeaf.h"

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