#ifndef IWORLD_H_
#define IWORLD_H_

#include <string>
#include <vector>

class Actor;
class IScene;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	//���z�f�X�g���N�^
	virtual ~IWorld() = default;

	//�A�N�^�[��ǉ�
	virtual void add_actor(Actor* actor) = 0;
	//�A�N�^�[�̌���
	virtual Actor* find_actor(const std::string& name) const = 0;
	//�w�肵���^�O�������A�N�^�[�̌���
	virtual std::vector<Actor*> find_actor_with_tag(const std::string& tag) const = 0;
	//�A�N�^�[����Ԃ�
	virtual int count_actor() const = 0;
	//�w�肵���^�O�������A�N�^�[����Ԃ�
	virtual int count_actor_with_tag(const std::string& tag) const = 0;
	//���b�Z�[�W�̑��M
	virtual void send_message(const std::string& message, void* param = nullptr) = 0;

	//�V�[���̐؂�ւ�
	virtual void sub_scene_change(int area_num) = 0;

	//�����X�^�[�G���A�̐ݒ�
	virtual void set_monster_area(const int monster_area) = 0;
	//�����X�^�[�G���A�̎擾
	virtual int monster_area() const = 0;

	//�A�C�e���I�u�W�F�N�g�̔z�u
	virtual void set_item_object(const int area_num) = 0;

	//�V�[���̎擾
	virtual IScene* scene() = 0;
};

#endif // !IWORLD_H_
