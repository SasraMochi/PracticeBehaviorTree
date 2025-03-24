#pragma once
#include "NodeResult.h"

class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ����
	virtual NodeResult Run() = 0;

	// ���Z�b�g
	virtual void Reset();

protected:
	// �����Ăяo�������`�F�b�N����
	void CheckFirstRun();

private:
	void SetRunnning();

protected:
	NodeResult mNodeResult = NodeResult::None;
};