#pragma once
#include "NodeResult.h"

class INode {
public:
	// 仮想デストラクタ
	virtual ~INode() = default;

	// 初期化
	virtual void init() = 0;

	// 動作
	virtual NodeResult tick() = 0;

	// リセット
	virtual void reset();
};