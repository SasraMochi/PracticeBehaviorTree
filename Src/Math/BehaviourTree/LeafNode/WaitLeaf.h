#pragma once

#include "Math/BehaviourTree/INode.h"

class WaitLeaf : public INode {
public:
	WaitLeaf(BlackBoard* black_board, const float wait_time);
	~WaitLeaf();

	NodeResult tick() override;

	void reset() override;

private:
	float mWaitTime = 0.f;
	float mWaitCount = 0.f;
};