#include "CheckNearPlayer.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

CheckNearPlayer::CheckNearPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance)
	: BranchNode(black_board, true_node, false_node),
	mMaxDistance(max_distance) {
}

CheckNearPlayer::~CheckNearPlayer()
{
}

NodeResult CheckNearPlayer::tick() {
	check_first_run();

	if (is_near_player()) {
		mNodeResult = mpTrueNode->tick();
	}
	else {
		mNodeResult = mpFalseNode->tick();
	}

	return mNodeResult;
}

const bool CheckNearPlayer::is_near_player()
{
	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	// 近ければtrueを返す
	return vector.magnitude() < mMaxDistance;
}
