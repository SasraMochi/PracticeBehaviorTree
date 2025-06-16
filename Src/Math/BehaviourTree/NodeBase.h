#pragma once

#include "Math/BehaviourTree/INode.h"

class BlackBoard;

/// <summary>
/// 各ノードが継承する基底クラス
/// </summary>
class NodeBase : public INode {
public:
	void set_node_id(const int id) override { mNodeId = id; }

protected:
	explicit NodeBase(BlackBoard* black_board) : mpBlackBoard{ black_board } {}
	virtual ~NodeBase() = default;

	virtual void init() override {
		mNodeResult = NodeResult::Running;
	}

	virtual void tick() override {}

	virtual void finalize() override {}

	virtual NodeResult get_node_result() const {
		return mNodeResult;
	}

	virtual int get_running_node_id() const override { return mNodeId; }

	NodeResult mNodeResult = NodeResult::Idle; // ノードの状態
	BlackBoard* mpBlackBoard = nullptr; // ブラックボード

private:
	int mNodeId = -1;
};