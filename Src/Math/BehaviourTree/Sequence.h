#pragma once

#include <vector>
#include "Composite.h"

class Sequence : public Composite {
public:
	Sequence();

	~Sequence();

public:
	virtual NodeResult Run() override;
};