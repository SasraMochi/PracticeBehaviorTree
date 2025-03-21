#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include"IScene.h"

class GamePlayScene : public IScene {
public:
	//開始
	virtual void start() override;
	//更新
	virtual void update() override;
	//描画
	virtual void draw() const override;

	//終了しているか？
	virtual bool is_end() const override;

	//終了
	virtual void end() override;
};

#endif // !TITLE_SCENE_H_