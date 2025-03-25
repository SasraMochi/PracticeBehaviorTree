#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(INode* node)
{
	SetNode(node);
}

Inverter::~Inverter()
{
}

NodeResult Inverter::Run()
{
	CheckFirstRun();

	// 結果が出るまで回し続ける
	NodeResult result = NodeResult::None;
	do {
		result = mChildNode->Run();
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
	mNodeResult = NodeResult::None;
	return mNodeResult;
}
