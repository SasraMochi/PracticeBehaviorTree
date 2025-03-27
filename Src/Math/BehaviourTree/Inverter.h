#pragma once

#include "Decorator.h"

class Inverter : public Decorator {
public:
	Inverter(BlackBoard* black_board, INode* node);

	~Inverter();

public:
	virtual NodeResult Run() override;
};