#pragma once

#include <vector>
#include "Math/BehaviourTree/CompositeNode/CompositeNodeBase.h"

class Sequence : public CompositeNodeBase {
public:
	explicit Sequence(BlackBoard* black_board);

	~Sequence();

	void tick() override;

private:
	const int get_next_index() const override;
	void node_increment() override;
};