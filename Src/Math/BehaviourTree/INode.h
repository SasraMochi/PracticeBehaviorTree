#pragma once
#include "NodeResult.h"
#include "Actor/Actor.h"

class INode {
public:
	// 仮想デストラクタ
	virtual ~INode() = default;

	// 動作
	virtual NodeResult Run() = 0;

	// リセット
	virtual void Reset();

	// オーナーをセットする
	void SetOwner(Actor* actor);

protected:
	// 初期呼び出し時かチェックする
	void CheckFirstRun();

private:
	void SetRunnning();

protected:
	Actor* mpOwner = nullptr;

	NodeResult mNodeResult = NodeResult::None;
};