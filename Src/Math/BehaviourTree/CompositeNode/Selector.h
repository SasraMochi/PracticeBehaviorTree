#pragma once

#include <vector>
#include "Math/BehaviourTree/CompositeNode/CompositeNodeBase.h"

class Selector : public CompositeNodeBase {
public:
	explicit Selector(BlackBoard* black_board);

	~Selector();

	void init() override;
	void tick() override;
	void reset() override;

private:
	void node_increment();

private:
	// ���ݓ������Ă���Node
	int mRunningNodeIndex{ 0 };
};