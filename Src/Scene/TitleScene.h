#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include"IScene.h"

class TitleScene : public IScene {
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
	bool is_end_;
};

#endif // !TITLE_SCENE_H_