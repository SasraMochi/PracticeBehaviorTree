#pragma once
#include "NodeResult.h"

class INode {
public:
	// 仮想デストラクタ
	virtual ~INode() = default;

	// 動作
	virtual NodeResult Run() = 0;

	// 初期呼び出し時かチェックする
	void CheckFirstRun();

	// リセット
	virtual void Reset();

private:
	void SetRunnning();

protected:
	NodeResult mNodeResult = NodeResult::None;
};