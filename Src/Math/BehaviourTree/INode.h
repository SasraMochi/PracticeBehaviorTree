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
	// 後処理
	virtual void finalize() = 0;
	// ノードの状態を取得
	virtual NodeResult get_node_result() const = 0;
	// ノードのIDを保存
	virtual void set_node_id(const int id) = 0;
	// 現在動作中のノードのIDを取得
	virtual int get_running_node_id() const = 0;
};