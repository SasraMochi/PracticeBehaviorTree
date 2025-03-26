#pragma once
#include "NodeResult.h"
#include "Actor/Actor.h"

class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;

	// ����
	virtual NodeResult Run() = 0;

	// ���Z�b�g
	virtual void Reset();

	// �I�[�i�[���Z�b�g����
	void SetOwner(Actor* actor);

protected:
	// �����Ăяo�������`�F�b�N����
	void CheckFirstRun();

private:
	void SetRunnning();

protected:
	Actor* mpOwner = nullptr;

	NodeResult mNodeResult = NodeResult::None;
};