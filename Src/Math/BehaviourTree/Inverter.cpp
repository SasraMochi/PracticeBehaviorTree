#include "Inverter.h"

Inverter::Inverter()
{
}

Inverter::~Inverter()
{
}

NodeResult Inverter::Run()
{
	CheckFirstRun();

	NodeResult result = NodeResult::None;

	// 成功か失敗を返すまで実行
	// doで先に実行しておく
	do {
		result = mChildNode->Run();
	} while (result == NodeResult::Running);

	if (result == NodeResult::Success) {
		return NodeResult::Fail;
	}
	else if (result == NodeResult::Fail) {
		return NodeResult::Success;
	}

	// 普通はここまで実行されることはない
	// TODO 後々アサート呼ぶ
	return NodeResult::None;
}
