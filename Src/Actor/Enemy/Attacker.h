#pragma once

#include "Actor/Actor.h"
#include "Math/BehaviourTree/Selector.h"

class Attacker : public Actor {
public:
	//�R���X�g���N�^
	Attacker();
	//�f�X�g���N�^
	~Attacker();
	//�X�V
	virtual void update(float delta_time);
	//�`��
	virtual void draw() const;
	//�������̕`��
	virtual void draw_transparent() const;
	//GUI�̕`��
	virtual void draw_gui() const;

private:
	Selector* mpBehaviourTree = nullptr;
};
