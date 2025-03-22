#pragma once

#include"IScene.h"
#include "World/World.h"

class GamePlayScene : public IScene {
public:
	//�J�n
	virtual void start() override;
	//�X�V
	virtual void update() override;
	//�`��
	virtual void draw() const override;

	//�I�����Ă��邩�H
	virtual bool is_end() const override;

	//�I��
	virtual void end() override;

private:
	World mWorld;

	bool mIsEnd = false;
};