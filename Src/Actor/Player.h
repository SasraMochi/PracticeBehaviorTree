#pragma once

#include "Actor.h"
#include "Math/Vector2.h"

class Player : public Actor{
public:
	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();

	// �X�V
	virtual void update(float delta_time);

	// �`��
	virtual void draw() const;

	//�������̕`��
	virtual void draw_transparent() const;

	//GUI�̕`��
	virtual void draw_gui() const;

private:
	float mSpeed = 4.f;
	float mHealth = 100.f;
};