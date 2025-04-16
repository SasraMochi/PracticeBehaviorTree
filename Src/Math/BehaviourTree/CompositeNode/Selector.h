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
	// åªç›ìÆÇ©ÇµÇƒÇ¢ÇÈNode
	int mRunningNodeIndex{ 0};
};