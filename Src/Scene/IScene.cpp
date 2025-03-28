#include "IScene.h"

//次のシーンを設定
void IScene::set_next(const std::string& next_scene){
	mNextScene = next_scene;
}

//ゲームスピードを設定
void IScene::set_game_speed(const float game_speed){
	mGameSpeed = game_speed;
}

//ゲームスピードを取得
float IScene::game_speed() const{
	return mGameSpeed;
}

//次のシーンを返す
std::string IScene::next() const{
	return mNextScene;
}