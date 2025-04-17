#include "CompositeNodeBase.h"

CompositeNodeBase::~CompositeNodeBase()
{
	for (auto node : mChildNodes) {
		delete node;
	}
	mChildNodes.clear();
}

void CompositeNodeBase::init()
{
	NodeBase::init();
	mRunningNodeIndex = 0;

	// �ŏ��̃m�[�h��������
	if (mChildNodes.size() > 0) {
		mChildNodes[mRunningNodeIndex]->init();
	}
	else {
		mNodeResult = NodeResult::Fail;
	}
}

void CompositeNodeBase::add_node(INode* node)
{
	mChildNodes.push_back(node);
}

void CompositeNodeBase::node_increment()
{
	// ���݂̃m�[�h�̌�n��
	mChildNodes[mRunningNodeIndex]->finalize();

	// �C���f�b�N�X��i�߂�
	mRunningNodeIndex = get_next_index();

	// �������ׂĂ̎q�m�[�h�������Ă����s������
	if (mRunningNodeIndex > mChildNodes.size() - 1) {
		mNodeResult = NodeResult::Fail;
		init();
		return;
	}

	// ���ɉ񂷃m�[�h�̏�����
	mChildNodes[mRunningNodeIndex]->init();
}
