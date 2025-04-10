#include "CircleAttackLeaf.h"

#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

#include "DxLib.h"
CircleAttackLeaf::CircleAttackLeaf(BlackBoard* black_board)
	: INode(black_board)
{
}

CircleAttackLeaf::~CircleAttackLeaf()
{
}

NodeResult CircleAttackLeaf::tick()
{
	check_first_run();

	// UŒ‚
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");
	agent->attack();

	return NodeResult::Success;
}
