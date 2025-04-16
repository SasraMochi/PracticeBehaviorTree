#pragma once

#include "Math/BehaviourTree/INode.h"

class BlackBoard;

// 各ノードの基底クラス
class NodeBase : INode {
protected:
	explicit NodeBase(BlackBoard* black_board) : mpBlackBoard{ black_board } {}
	virtual ~NodeBase() = default;

private:
	NodeResult mNodeResult = NodeResult::Idle; // ノードの状態
	BlackBoard* mpBlackBoard = nullptr; // ブラックボード
};