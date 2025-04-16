#pragma once

#include "Math/BehaviourTree/INode.h"

class EscapeFromPlayerLeaf : public INode {
public:
	EscapeFromPlayerLeaf(BlackBoard* black_board);

	~EscapeFromPlayerLeaf();

	NodeResult tick() override;

private:
	void escape_from_player();
};