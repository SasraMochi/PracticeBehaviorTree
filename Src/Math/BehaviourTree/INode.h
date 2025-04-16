#pragma once
#include "NodeResult.h"

class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ������
	virtual void init() = 0;

	// ����
	virtual NodeResult tick() = 0;

	// ���Z�b�g
	virtual void reset();
};