#pragma once

#include <vector>
#include "Composite.h"

class Sequence : public Composite {
public:
	Sequence(BlackBoard* black_board);

	~Sequence();

public:
	virtual NodeResult Run() override;
};