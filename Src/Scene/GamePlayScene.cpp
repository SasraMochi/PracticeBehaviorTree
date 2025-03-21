#include "GamePlayScene.h"
#include "DxLib.h"

void GamePlayScene::start() {

}

void GamePlayScene::update() {

}

void GamePlayScene::draw() const {
	DrawString(0, 0, "ゲームプレイシーン", GetColor(255, 255, 255));
}

bool GamePlayScene::is_end() const {
	return false;
}

void GamePlayScene::end() {

}