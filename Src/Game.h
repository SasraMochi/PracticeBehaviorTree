#pragma once
#include "DxLib.h"
#include "Scene/SceneManager.h"

class Game {
public:
	//コンストラクタ
	Game(int screenX = 640, int screenY = 480);

	//開始
	void start();

	//更新
	void update();

	//描画
	void draw();

	//終了
	void end();

private:
	//シーンマネージャー
	SceneManager scene_manager_;
};