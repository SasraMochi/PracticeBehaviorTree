#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 指定した時間待機する葉ノード
/// </summary>
class WaitLeaf : public LeafNodeBase {
public:
	explicit WaitLeaf(BlackBoard* black_board, const float wait_time);
	~WaitLeaf();

	void tick() override;
	void finalize() override;

private:
	float mWaitTime = 0.f;
	float mWaitCount = 0.f;
};