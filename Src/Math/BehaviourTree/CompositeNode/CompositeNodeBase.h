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

	virtual void init() override;
	virtual void finalize() override;

protected:
	virtual const int get_next_index() const = 0;
	
public:
	void add_node(INode* node);

protected:
	void node_increment();

protected:
	// 子ノード群
	std::vector<INode*> mChildNodes;
	// 現在動かしているノードのインデックス
	int mRunningNodeIndex{ 0 };
};