#pragma once

#include"IScene.h"
#include "World/World.h"

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

private:
	World mWorld;

	bool mIsEnd = false;
};