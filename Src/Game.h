#pragma once
#include "DxLib.h"
#include "Scene/SceneManager.h"

class Game {
public:
	//�R���X�g���N�^
	Game();

	//�J�n
	void start();

	//�X�V
	void update();

	//�`��
	void draw();

	//�I��
	void end();

private:
	//�V�[���}�l�[�W���[
	SceneManager mSceneManager;
};