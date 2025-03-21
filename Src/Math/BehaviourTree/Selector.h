#pragma once

#include <vector>
#include "Composite.h"

class Selector : public Composite {
public:
	Selector();

	~Selector();

public:
	virtual NodeResult Run() override;
};