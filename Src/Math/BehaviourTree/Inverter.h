#pragma once

#include "Decorator.h"

class Inverter : public Decorator {
public:
	Inverter();

	~Inverter();

public:

	using Node::Run;

	virtual NodeResult Run() override;
};