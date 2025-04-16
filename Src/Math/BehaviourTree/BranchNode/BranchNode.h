#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// ブランチノードの基底クラス
/// </summary>
class BranchNode : public NodeBase {
public:
	explicit BranchNode(BlackBoard* black_board, INode* true_node, INode* false_node);
	virtual ~BranchNode();

	virtual void init() override;
	virtual void tick() override;
	virtual void reset() override;

protected:
	// 条件を満たしているか
	virtual const bool is_condition() = 0;

protected:
	INode* mpBranchNodes[2] = { nullptr, nullptr }; // ブランチノードの配列
	int mSatisfyIndex = -1; // 条件を満たしているノードのインデックス
};
