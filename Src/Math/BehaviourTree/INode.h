#pragma once
#include "NodeResult.h"

class BlackBoard;

class INode {
public:
	// コンストラクタ
	explicit INode(BlackBoard* black_board);

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
	BlackBoard* mpBlackBoard = nullptr;

	NodeResult mNodeResult = NodeResult::None;
};