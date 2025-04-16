#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(BlackBoard* black_board, INode* child_node)
	: DecoratorNodeBase(black_board)
{
	set_node(child_node);
}

Inverter::~Inverter()
{
}

NodeResult Inverter::tick()
{
	check_first_run();

	// 結果が出るまで回し続ける
	NodeResult result = NodeResult::Idle;
	do {
		result = mChildNode->tick();
	} while (result == NodeResult::Running);

	// 結果を反転させる
	if (result == NodeResult::Success) {
		mNodeResult = NodeResult::Fail;
		return mNodeResult;
	}
	else if (result == NodeResult::Fail) {
		mNodeResult = NodeResult::Success;
		return mNodeResult;
	}

	// 普通はここまで実行されることはない
	// TODO 後々アサート呼ぶ
	assert(!"結果が不正です");
	mNodeResult = NodeResult::Idle;
	return mNodeResult;
}
