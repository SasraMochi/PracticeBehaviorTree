#pragma once

#include "Math/BehaviourTree/INode.h"

class BlackBoard;

/// <summary>
/// 各ノードが継承する基底クラス
/// </summary>
class NodeBase : public INode {
protected:
	explicit NodeBase(BlackBoard* black_board) : mpBlackBoard{ black_board } {}
	virtual ~NodeBase() = default;

	NodeResult get_node_result() const {
		return mNodeResult;
	}

	virtual void init() override {
		mNodeResult = NodeResult::Running;
	}

	virtual void finalize() override {
		mNodeResult = NodeResult::Idle;
	}

	NodeResult mNodeResult = NodeResult::Idle; // ノードの状態
	BlackBoard* mpBlackBoard = nullptr; // ブラックボード
};