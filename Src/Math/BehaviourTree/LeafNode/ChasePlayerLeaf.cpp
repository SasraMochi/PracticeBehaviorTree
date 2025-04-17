#include "ChasePlayerLeaf.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"


ChasePlayerLeaf::ChasePlayerLeaf(BlackBoard* black_board)
	: LeafNodeBase(black_board)
{
}

ChasePlayerLeaf::~ChasePlayerLeaf()
{
}

void ChasePlayerLeaf::tick()
{
	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	agent->move_towards(vector.normalized(), 3.25f);
}

NodeResult ChasePlayerLeaf::get_node_result() const
{
	// 必ず成功を返す
	return NodeResult::Success;
}
