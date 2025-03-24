#pragma once
#include "NodeResult.h"

class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ����
	virtual NodeResult Run() = 0;

	// �����Ăяo�������`�F�b�N����
	void CheckFirstRun();

	// ���Z�b�g
	virtual void Reset();

private:
	void SetRunnning();

protected:
	NodeResult mNodeResult = NodeResult::None;
};