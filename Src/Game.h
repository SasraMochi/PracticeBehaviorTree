#pragma once
#include "DxLib.h"
#include "Scene/SceneManager.h"

class Game {
public:
	//コンストラクタ
	Game();

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
	SceneManager mSceneManager;
};