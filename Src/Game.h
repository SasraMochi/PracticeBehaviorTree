#pragma once
#include "DxLib.h"
#include "Scene/SceneManager.h"

class Game {
public:
	//コンストラクタ
	Game(const int screenX, const int screenY);

	//開始
	void start();

	//更新
	void update();

	//描画
	void draw();

	//デバッグ描画
	void draw_debug();

	//終了
	void end();

private:
	//シーンマネージャー
	SceneManager scene_manager_;
};