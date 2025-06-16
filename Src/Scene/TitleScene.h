#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include"IScene.h"

class TitleScene : public IScene {
public:
	//開始
	virtual void start() override;
	//更新
	virtual void update() override;
	//描画
	virtual void draw() const override;
	//デバッグ描画
	virtual void draw_debug() override;

	//終了しているか？
	virtual bool is_end() const override;

	//終了
	virtual void end() override;

private:
	// シーン切り替え予約
	void change_scene_(std::string next_scene_name);

private:
	bool mIsEnd;
};

#endif // !TITLE_SCENE_H_