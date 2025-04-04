#pragma once

#include "Math/BehaviourTree/INode.h"

class ConditionalBranch : public INode {
public:
	ConditionalBranch(BlackBoard* black_board, INode* true_node, INode* false_node);
	~ConditionalBranch();
public:
	void reset() override;

protected:
	INode* mpTrueNode = nullptr;
	INode* mpFalseNode = nullptr;
};
