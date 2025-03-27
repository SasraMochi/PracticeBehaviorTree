#pragma once

#include "Actor/Actor.h"
#include "Actor/IAgent.h"
#include "Math/BehaviourTree/Selector.h"

#include "Math/Vector2.h"

class IWorld;

class Attacker : public Actor, public IAgent {
public:
	//�R���X�g���N�^
	Attacker(IWorld* world);
	//�f�X�g���N�^
	~Attacker();
	//�X�V
	void update(float delta_time);
	//�`��
	void draw() const;
	//�������̕`��
	void draw_transparent() const;
	//GUI�̕`��
	void draw_gui() const;

public:
	const Vector2& GetPosition() const override;
	void MoveTowards(const Vector2& target, float speed) override;

private:
	INode* mpBehaviourTree = nullptr;

	// Vector2 mPlayerPosition = { 0.f, 0.f };
};
