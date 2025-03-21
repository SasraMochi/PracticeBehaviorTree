#include "TitleScene.h"
#include<DxLib.h>

void TitleScene::start(){
	is_end_ = false;

	set_next("GamePlayScene");
}

void TitleScene::update(){
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		is_end_ = true;
	}
}

void TitleScene::draw() const {
	DrawString(0, 0, "タイトルシーン", GetColor(255, 255, 255));
}

bool TitleScene::is_end() const {
	return is_end_;
}

void TitleScene::end() {

}