#pragma once

#include <vector>
#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �R���|�W�b�g�m�[�h�̊��N���X
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
	// �q�m�[�h�Q
	std::vector<INode*> mChildNodes;
	// ���ݓ������Ă���m�[�h�̃C���f�b�N�X
	int mRunningNodeIndex{ 0 };
};