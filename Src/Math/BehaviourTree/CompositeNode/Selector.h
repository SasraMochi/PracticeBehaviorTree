#pragma once

#include <vector>
#include "Math/BehaviourTree/CompositeNode/CompositeNodeBase.h"

class Selector : public CompositeNodeBase {
public:
	explicit Selector(BlackBoard* black_board);

	~Selector();

	void tick() override;

private:
	const int get_next_index() const override;
	void node_increment() override;
};