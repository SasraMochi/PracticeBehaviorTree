#include "World/World.h"
#include "Scene/IScene.h"
#include "Actor/Actor.h"

//�f�X�g���N�^
World::~World() {
	clear();
}

//�X�V
void World::update(float delta_time) {
	//�A�N�^�[�̍X�V
	actors_.update(delta_time);
	//�A�N�^�[�̏Փ�
	actors_.collide();
	//�A�N�^�[�̒x���X�V
	actors_.late_update(delta_time);
	//�A�N�^�[�̏���
	actors_.remove();
}

//�`��
void World::draw() const {
	//�A�N�^�[�̕`��
	actors_.draw();
	//�������A�N�^�[�̕`��
	actors_.draw_transparent();
	//GUI�̕`��
	actors_.draw_gui();
}

//����
void World::clear() {
	//�A�N�^�[�̏���
	actors_.clear();
}

//�V�[���̓o�^
void World::set_scene(IScene* scene) {
	scene_ = scene;
}

//�V�[���̎擾
IScene* World::scene() {
	return scene_;
}

//�A�N�^�[�̒ǉ�
void World::add_actor(Actor* actor) {
	actors_.add(actor);
}

//�A�N�^�[�̌���
Actor* World::find_actor(const std::string& name) const {
	return actors_.find(name);
}

//�w�肵���^�O�������A�N�^�[�̌���
std::vector<Actor*> World::find_actor_with_tag(const std::string& tag) const {
	return actors_.find_with_tag(tag);
}

//�A�N�^�[����Ԃ�
int World::count_actor() const {
	return actors_.count();
}

//�w�肵���^�O�������A�N�^�[����Ԃ�
int World::count_actor_with_tag(const std::string& tag) const {
	return actors_.count_with_tag(tag);
}

//���b�Z�[�W���M
void World::send_message(const std::string& message, void* param) {
	actors_.send_message(message, param);
}