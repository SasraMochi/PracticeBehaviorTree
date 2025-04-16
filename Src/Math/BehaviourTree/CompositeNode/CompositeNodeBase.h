#pragma once

#include <vector>
#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// コンポジットノードの基底クラス
/// </summary>
class CompositeNodeBase : public NodeBase {
public:
	explicit CompositeNodeBase(BlackBoard* black_board) : NodeBase(black_board) {
	};

	virtual ~CompositeNodeBase();

	void add_node(INode* node);

protected:
	std::vector<INode*> mChildNodes;
};