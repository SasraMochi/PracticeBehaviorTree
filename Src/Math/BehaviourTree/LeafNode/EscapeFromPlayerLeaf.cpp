#include "EscapeFromPlayerLeaf.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

EscapeFromPlayerLeaf::EscapeFromPlayerLeaf(BlackBoard* black_board)
	: INode(black_board)
{
}

EscapeFromPlayerLeaf::~EscapeFromPlayerLeaf()
{
}

NodeResult EscapeFromPlayerLeaf::tick()
{
	check_first_run();

	escape_from_player();

	return NodeResult::Success;
}

void EscapeFromPlayerLeaf::escape_from_player()
{
	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = agent->get_position() - player_pos;

	agent->move_towards(vector.normalized(), 3.f);
}
