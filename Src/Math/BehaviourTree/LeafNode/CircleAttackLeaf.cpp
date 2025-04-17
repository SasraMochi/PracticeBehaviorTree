#include "CircleAttackLeaf.h"

#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

#include "DxLib.h"
CircleAttackLeaf::CircleAttackLeaf(BlackBoard* black_board)
	: LeafNodeBase(black_board)
{
}

CircleAttackLeaf::~CircleAttackLeaf()
{
}

void CircleAttackLeaf::tick()
{
	// UŒ‚
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");
	agent->attack();
}

NodeResult CircleAttackLeaf::get_node_result() const
{
	// •K‚¸¬Œ÷‚ğ•Ô‚·
	return NodeResult::Success;
}
