#pragma once

#include "Decorator.h"

class Inverter : public Decorator {
public:
	Inverter(BlackBoard* black_board, INode* child_node);

	~Inverter();

public:
	virtual NodeResult tick() override;
};