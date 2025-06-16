#include "TitleScene.h"
#include<DxLib.h>

void TitleScene::start(){
	mIsEnd = false;
}

void TitleScene::update(){
	if (CheckHitKey(KEY_INPUT_Z)) 
	{
		change_scene_("GamePlayScene");
	}
	else if (CheckHitKey(KEY_INPUT_A)) 
	{
		change_scene_("EditBehaviorTreeScene");
	}
}

void TitleScene::draw() const {
	DrawString(0, 0, "タイトルシーン", GetColor(255, 255, 255));
}

void TitleScene::draw_debug()
{
}

bool TitleScene::is_end() const {
	return mIsEnd;
}

void TitleScene::end() {

}

void TitleScene::change_scene_(std::string next_scene_name)
{
	set_next(next_scene_name);
	mIsEnd = true;
}
