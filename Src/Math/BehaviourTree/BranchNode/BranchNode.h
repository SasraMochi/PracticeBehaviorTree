#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �u�����`�m�[�h�̊��N���X
/// </summary>
class BranchNode : public NodeBase {
public:
	explicit BranchNode(BlackBoard* black_board, INode* true_node, INode* false_node);
	virtual ~BranchNode();

	virtual void init() override;
	virtual void tick() override;
	virtual void reset() override;

protected:
	// �����𖞂����Ă��邩
	virtual const bool is_condition() = 0;

protected:
	INode* mpBranchNodes[2] = { nullptr, nullptr }; // �u�����`�m�[�h�̔z��
	int mSatisfyIndex = -1; // �����𖞂����Ă���m�[�h�̃C���f�b�N�X
};
