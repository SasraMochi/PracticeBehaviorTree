#pragma once
#include "NodeResult.h"

class INode {
public:
	// 仮想デストラクタ
	virtual ~INode() = default;

	// 動作
	virtual NodeResult Run() = 0;

	// リセット
	virtual void Reset();

protected:
	// 初期呼び出し時かチェックする
	void CheckFirstRun();

private:
	void SetRunnning();

protected:
	NodeResult mNodeResult = NodeResult::None;
};