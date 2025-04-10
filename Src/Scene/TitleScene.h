#pragma once

#include"IScene.h"

class TitleScene : public IScene {
public:
	//�J�n
	void start() override;
	//�X�V
	void update() override;
	//�`��
	void draw() const override;

	//�I�����Ă��邩�H
	bool is_end() const override;

	//�I��
	void end() override;

private:
	bool mIsEnd = false;
};