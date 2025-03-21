#pragma once
#include "NodeResult.h"

class Node {
public:
	Node();

	virtual ~Node();

	virtual NodeResult Run();

protected:
	NodeResult mNodeResult = NodeResult::None;
};