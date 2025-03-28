#include "TitleScene.h"
#include<DxLib.h>

void TitleScene::start(){
	mIsEnd = false;

	set_next("GamePlayScene");
}

void TitleScene::update(){
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		mIsEnd = true;
	}
}

void TitleScene::draw() const {
	DrawString(0, 0, "タイトルシーン", GetColor(255, 255, 255));
}

bool TitleScene::is_end() const {
	return mIsEnd;
}

void TitleScene::end() {

}