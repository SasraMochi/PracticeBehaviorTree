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

NodeResult ChasePlayerLeaf::Run()
{
	CheckFirstRun();

	// プレイヤーの位置を取得
	auto player_pos = mpBlackBoard->GetValue<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->GetValue<IAgent*>("Agent");

	auto vector = player_pos - agent->GetPosition();

	agent->MoveTowards(vector.normalized(), 3.f);

	return NodeResult::Success;
}
