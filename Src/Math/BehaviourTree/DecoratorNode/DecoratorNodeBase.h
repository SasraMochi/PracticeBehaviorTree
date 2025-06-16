#pragma once

#include "Math/BehaviourTree/NodeBase.h"

class DecoratorNodeBase : public NodeBase {
public:
	explicit DecoratorNodeBase(BlackBoard* black_board) : NodeBase(black_board) {}
	virtual ~DecoratorNodeBase();

	virtual void init() override;
	virtual void finalize() override;

	void set_node(INode* node);

	int get_running_node_id() const override;

protected:
	INode* mChildNode = nullptr;
};