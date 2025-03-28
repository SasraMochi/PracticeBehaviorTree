#include "IScene.h"

//���̃V�[����ݒ�
void IScene::set_next(const std::string& next_scene){
	mNextScene = next_scene;
}

//�Q�[���X�s�[�h��ݒ�
void IScene::set_game_speed(const float game_speed){
	mGameSpeed = game_speed;
}

//�Q�[���X�s�[�h���擾
float IScene::game_speed() const{
	return mGameSpeed;
}

//���̃V�[����Ԃ�
std::string IScene::next() const{
	return mNextScene;
}