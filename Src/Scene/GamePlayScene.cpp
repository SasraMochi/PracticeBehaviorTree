#include "GamePlayScene.h"
#include "DxLib.h"

void GamePlayScene::start() {
}

void GamePlayScene::update() {
	float delta_time = 1.f;

	mWorld.update(delta_time);
}

void GamePlayScene::draw() const {
	mWorld.draw();

	DrawString(0, 0, "ゲームプレイシーン", GetColor(255, 255, 255));
}

bool GamePlayScene::is_end() const {
	return false;
}

void GamePlayScene::end() {

}