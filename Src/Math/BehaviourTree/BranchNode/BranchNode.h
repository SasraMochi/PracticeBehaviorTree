#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �u�����`�m�[�h�̊��N���X
/// </summary>
class BranchNode : public NodeBase {
public:
	explicit BranchNode(BlackBoard* black_board, INode* true_node, INode* false_node);
	virtual ~BranchNode();

	virtual void reset() override;

protected:
	INode* mpTrueNode = nullptr;
	INode* mpFalseNode = nullptr;
};
