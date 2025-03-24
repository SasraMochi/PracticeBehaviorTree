#include "GamePlayScene.h"
#include "DxLib.h"

#include "Actor/Enemy/Attacker.h"

void GamePlayScene::start() {
	set_next("TitleScene");

	mWorld.add_actor(new Attacker());
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