#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include"IScene.h"

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
};

#endif // !TITLE_SCENE_H_