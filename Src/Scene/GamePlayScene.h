#pragma once

#include"IScene.h"
#include "World/World.h"

class GamePlayScene : public IScene {
public:
	//�J�n
	void start() override;
	//�X�V
	void update() override;
	//�`��
	void draw() const override;
	//�f�o�b�O�`��
	virtual void draw_debug() override;

	//�I�����Ă��邩�H
	bool is_end() const override;

	//�I��
	void end() override;

private:
	World mWorld;

	bool mIsEnd = false;
};