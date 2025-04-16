#pragma once
#include "NodeResult.h"

/// <summary>
/// ノードのインターフェース
/// </summary>
class INode {
public:
	// 仮想デストラクタ
	virtual ~INode() = default;

	// 初期化
	virtual void init() = 0;

	// 動作
	virtual void tick() = 0;

	// リセット
	virtual void reset() = 0;

	// ノードの状態を取得
	virtual NodeResult get_node_result() const = 0;
};