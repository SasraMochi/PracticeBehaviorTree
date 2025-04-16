#pragma once

#include <vector>
#include "Composite.h"

class Selector : public CompositeNodeBase {
public:
	Selector(BlackBoard* black_board);

	~Selector();

	void reset() override;

public:
	virtual NodeResult tick() override;

	void node_increment();

private:
	// ���ݓ������Ă���Node
	int mRunningNodeIndex{ 0};
};