#pragma once

#include "Decorator.h"

class Inverter : public Decorator {
public:
	Inverter(INode* node);

	~Inverter();

public:
	virtual NodeResult Run() override;
};