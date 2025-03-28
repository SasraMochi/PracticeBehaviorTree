#include "ChasePlayerLeaf.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"


ChasePlayerLeaf::ChasePlayerLeaf(BlackBoard* black_board)
	: INode(black_board)
{
}

ChasePlayerLeaf::~ChasePlayerLeaf()
{
}

NodeResult ChasePlayerLeaf::tick()
{
	check_first_run();

	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	agent->move_towards(vector.normalized(), 3.f);

	return NodeResult::Success;
}
