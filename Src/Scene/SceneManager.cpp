#include "SceneManager.h"
#include "SceneNull.h"

static SceneNull scene_null;	//null�V�[��

//�R���X�g���N�^
SceneManager::SceneManager() :
	mpCurrentScene{ &scene_null } {
}

//�f�X�g���N�^
SceneManager::~SceneManager() {
	clear();
}

//�X�V
void SceneManager::update() {
	//�V�[���̍X�V
	mpCurrentScene->update();
	//�V�[�����I�����Ă��邩�H
	if (mpCurrentScene->is_end()) {
		//�V�[����ύX����
		change(mpCurrentScene->next());
	}
}

//�`��
void SceneManager::draw() const {
	//���݂̃V�[����`��
	mpCurrentScene->draw();
}

//�I��
void SceneManager::end() {
	//���݂̃V�[�����I��
	mpCurrentScene->end();
	//null�V�[���ɂ��Ă���
	mpCurrentScene = &scene_null;
}

//�V�[���̒ǉ�
void SceneManager::add(const std::string& name, IScene* scene) {
	mScenes[name] = scene;
}

//�V�[���̕ύX
void SceneManager::change(const std::string& name, const std::string& next) {
	//���݂̃V�[�����I��
	end();
	//���݂̃V�[����ύX
	mpCurrentScene = mScenes[name];
	//���݂̃V�[����nextScene��ݒ�
	mpCurrentScene->set_next(next);
	//���݂̃V�[�����J�n
	mpCurrentScene->start();
}

//�V�[���̏���
void SceneManager::clear() {
	//�O�̈׃V�[���̏I�����Ăяo��
	end();
	//unordered_map���̃V�[�������ׂč폜
	for (const auto& pair : mScenes) {
		delete pair.second;	//�V�[���̍폜
	}
	//unordered_map������
	mScenes.clear();
}