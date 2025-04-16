#pragma once

#include "Decorator.h"

class Inverter : public DecoratorNodeBase {
public:
	Inverter(BlackBoard* black_board, INode* child_node);

	~Inverter();

public:
	virtual NodeResult tick() override;
};