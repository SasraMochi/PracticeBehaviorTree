#include "CheckFarPlayer.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

CheckFarPlayer::CheckFarPlayer(BlackBoard* black_board, INode* child_node, const float max_distance)
	: Decorator(black_board),
	mMaxDistance(max_distance) {
	set_node(child_node);
}

CheckFarPlayer::~CheckFarPlayer()
{
}

NodeResult CheckFarPlayer::tick() {
	check_first_run();

	// �v���C���[�̈ʒu���擾
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	// ����������Ă������̂ݎq�m�[�h�����s
	if (vector.magnitude() >= mMaxDistance) {
		auto result = mChildNode->tick();

		mNodeResult = result;
		return mNodeResult;
	}

	mNodeResult = NodeResult::Fail;
	return mNodeResult;
}