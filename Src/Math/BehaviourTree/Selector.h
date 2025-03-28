#pragma once

#include <vector>
#include "Composite.h"

class Selector : public Composite {
public:
	Selector(BlackBoard* black_board);

	~Selector();

public:
	virtual NodeResult tick() override;
};