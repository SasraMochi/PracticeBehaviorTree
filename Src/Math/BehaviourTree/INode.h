#pragma once
#include "NodeResult.h"

/// <summary>
/// �m�[�h�̃C���^�[�t�F�[�X
/// </summary>
class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ������
	virtual void init() = 0;

	// ����
	virtual void tick() = 0;

	// ���Z�b�g
	virtual void reset() = 0;

	// �m�[�h�̏�Ԃ��擾
	virtual NodeResult get_node_result() const = 0;
};