#include "CheckNearPlayer.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

CheckNearPlayer::CheckNearPlayer(BlackBoard* black_board, INode* child_node, const float max_distance)
	: Decorator(black_board),
	mMaxDistance(max_distance) {
	set_node(child_node);
}

CheckNearPlayer::~CheckNearPlayer()
{
}

NodeResult CheckNearPlayer::tick() {
	check_first_run();

	// プレイヤーの位置を取得
		// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	// 距離が離れていた場合は子ノードを実行
	if (vector.magnitude() >= mMaxDistance) {
		auto result = mChildNode->tick();

		mNodeResult = result;
		return mNodeResult;
	}

	mNodeResult = NodeResult::Fail;
	return mNodeResult;
}