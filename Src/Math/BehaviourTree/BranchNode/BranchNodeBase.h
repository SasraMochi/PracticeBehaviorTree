#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// ブランチノードの基底クラス
/// </summary>
class BranchNodeBase : public NodeBase {
public:
	explicit BranchNodeBase(BlackBoard* black_board, INode* true_node, INode* false_node);
	virtual ~BranchNodeBase();

	virtual void init() override;
	virtual void tick() override;
	virtual void finalize() override;

	int get_running_node_id() const override;

protected:
	// 条件を満たしているか   
	virtual const bool is_condition() = 0;
	
protected:
	INode* mpBranchNodes[2] = { nullptr, nullptr }; // ブランチノードの配列
	int mSatisfyIndex = -1; // 条件を満たしているノードのインデックス
};
