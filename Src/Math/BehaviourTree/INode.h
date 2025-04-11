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
	virtual NodeResult tick() = 0;

	// リセット
	virtual void reset();

protected:
	// 初期呼び出し時かチェックする
	void check_first_run();

private:
	// フラグを動作中に切り替える
	void set_running_();

protected:
	// 参照できるブラックボード
	BlackBoard* mpBlackBoard = nullptr;

	// 状態
	NodeResult mNodeResult = NodeResult::None;
};