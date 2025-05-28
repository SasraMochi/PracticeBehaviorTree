#include "EscapeFromPlayerLeaf.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

EscapeFromPlayerLeaf::EscapeFromPlayerLeaf(BlackBoard* black_board)
	: LeafNodeBase(black_board)
{
}

EscapeFromPlayerLeaf::~EscapeFromPlayerLeaf()
{
}

void EscapeFromPlayerLeaf::tick()
{
	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = agent->get_position() - player_pos;

	agent->move_towards(vector.normalized(), 3.f);
}

NodeResult EscapeFromPlayerLeaf::get_node_result() const
{
	// 必ず成功を返す
	return NodeResult::Success;
}
