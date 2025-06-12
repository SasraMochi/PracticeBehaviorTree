#pragma once

#include"IScene.h"
#include "World/World.h"

class GamePlayScene : public IScene {
public:
	//開始
	void start() override;
	//更新
	void update() override;
	//描画
	void draw() const override;
	//デバッグ描画
	virtual void draw_debug() override;

	//終了しているか？
	bool is_end() const override;

	//終了
	void end() override;

private:
	World mWorld;

	bool mIsEnd = false;
};