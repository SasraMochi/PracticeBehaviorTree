#pragma once

#include"IScene.h"

class TitleScene : public IScene {
public:
	//開始
	void start() override;
	//更新
	void update() override;
	//描画
	void draw() const override;

	//終了しているか？
	bool is_end() const override;

	//終了
	void end() override;

private:
	bool mIsEnd = false;
};