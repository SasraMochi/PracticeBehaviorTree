#pragma once

#include <string>
#include <vector>
#include "Math/Vector2.h"

class IWorld;	//���[���h���ۃC���^�[�t�F�[�X�̑O���錾
class BlackBoard;
class Vector2;

//�A�N�^�[�N���X
class Actor {
public:
	//�R���X�g���N�^
	Actor() = default;
	//���z�f�X�g���N�^
	virtual ~Actor() = default;
	//�X�V
	virtual void update(float delta_time);
	//�x���X�V
	virtual void late_update(float delta_time);
	//�`��
	virtual void draw() const;
	//�������̕`��
	virtual void draw_transparent() const;
	//GUI�̕`��
	virtual void draw_gui() const;
	//�Փ˃��A�N�V����
	virtual void react(Actor& other);
	//���b�Z�[�W����
	virtual void handle_message(const std::string& message, void* param);
	//�Փ˔���
	void collide(Actor& other);
	//���S����
	void die();
	//���S���Ă��邩�H
	bool is_dead() const;
	//���O���擾
	const std::string& name() const;
	//�^�O�����擾
	const std::string& tag() const;
	//���݈ʒu���擾
	const Vector2& position() const;

	//�U���͂��擾
	float attack_power() const;

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

protected:
	//���[���h
	IWorld* world_{ nullptr };
	//�u���b�N�{�[�h
	BlackBoard* black_board_{ nullptr };
	//�^�O��
	std::string tag_;
	//���O
	std::string name_;
	//�g�����X�t�H�[��
	Vector2 position_;
	//�ړ���
	Vector2 velocity_{ 0.0f,0.0f };
	//�Փ˔��肪�L�����H
	bool enable_collider_{ true };
	//���S�t���O
	bool dead_{ false };
	//�U����
	float attack_power_{ 0.0f };
};