#pragma once

#include "Actor/Actor.h"
#include "Actor/IAgent.h"
#include "Actor/ActorHealth.h"
#include "Math/BehaviourTree/Composite/Selector.h"

#include "Math/Vector2.h"
#include "UI/BarGauge.h"

#include "Math/MyTimer.h"

class IWorld;

class Attacker : public Actor, public IAgent {
	const float cCoolTime = 60.f;

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

	// �Փ˃��A�N�V����
	void react(Actor& other) override;

public:
	const Vector2& get_position() const override;
	void move_towards(const Vector2& target, float speed) override;

	const float get_health() const override;
	void attack() override;

private:
	void move(float delta_time);

private:
	INode* mpBehaviourTree = nullptr;
	BarGauge mHealthBar;
};
