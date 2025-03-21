#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector3.h"
#include <string>

// �N�H�[�^�j�I��
struct Quaternion {
	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };
	float w{ 1.0f };

	// �f�t�H���g�R���X�g���N�^
	Quaternion() = default;
	// �R���X�g���N�^
	Quaternion(float x, float y, float z, float w);

	// �P�ʃN�H�[�^�j�I��
	static Quaternion identity();
	// ��]���I�C���[�p�̒l�ŕԂ��܂�
	Vector3 euler_angles() const;
	void euler_angles(const Vector3& value);
	// ���K��
	Quaternion normalized() const;
	// [0] ��[1] ���g�p���� x �� y �����ɃA�N�Z�X���܂�
	float operator[](int index) const;
	float& operator[](int index);

	// ������ Quaternion �� x�Ay�Az�Aw �̐�����ݒ肵�܂�
	void set(float newX, float newY, float newZ, float newW);
	// fromDirection ���� toDirection �ւ̉�]���쐬���܂�
	void set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection);
	// �w�肳�ꂽ forward �� upwards �����ɉ�]���܂�
	void set_look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
	// ��]�����W�ɑ΂���p�x�̒l (AngleAxis) �ɕϊ����܂��B
	void to_angle_axis(float& angle, Vector3& axis);
	// �N�H�[�^��I���̒l�����₷�������������Ԃ��܂��B
	std::string to_string() const;

	// 2 �̉�] a �� b �Ԃ̊p�x��Ԃ��܂��B
	static float angle(const Quaternion& a, const Quaternion& b);
	// axis �̎���� angle �x��]�����]���쐬���܂��B
	static Quaternion angle_axis(float angle, const Vector3& axis);
	// 2 �̉�]�̓��ς�Ԃ��܂��B
	static float dot(const Quaternion& a, const Quaternion& b);
	// z���𒆐S��z�x�Ax���𒆐S��x�x�Ay���𒆐S��y�x��]�����]��Ԃ��܂��B
	static Quaternion euler(float x, float y, float z);
	static Quaternion euler(const Vector3& euler);
	// fromDirection ���� toDirection �ւ̉�]���쐬���܂��B
	static Quaternion from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection);
	// �t�N�H�[�^�j�I����Ԃ��܂�
	static Quaternion inverse(const Quaternion& rotation);
	// �w�肳�ꂽ forward �� upwards �����ɉ�]���܂�
	static Quaternion look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
	// ���K�������N�H�[�^�j�I����Ԃ��܂�
	static Quaternion normalize(const Quaternion& q);
	// from ���� to �ւ̉�]�𓾂܂�
	static Quaternion rotate_towards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);
	//�@a �� b �̊Ԃ� t �Ő��`�ɕ�Ԃ��܂��B�p�����[�^�[ t �́A[0, 1] �͈̔͂ł��B
	static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
	// a �� b �̊Ԃ� t �Ő��`�ɕ�Ԃ��܂��B�p�����[�^�[ t �́A�����Ă��܂���B
	static Quaternion lerp_unclamped(const Quaternion& a, const Quaternion& b, float t);
	//�@a �� b �̊Ԃ� t �ŋ���ɕ�Ԃ��܂��B�p�����[�^�[ t �́A[0, 1] �͈̔͂ł��B
	static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
	// a �� b �̊Ԃ� t �ŋ���ɕ�Ԃ��܂��B�p�����[�^�[ t �́A�����Ă��܂���B
	static Quaternion slerp_unclamped(const Quaternion& a, const Quaternion& b, float t);
	// ��r(���S�ɒl����v���Ă��邩�H�j
	bool equals(const Quaternion& other) const;
};

// ���Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator * (const Quaternion& lhs, float rhs);
Quaternion operator * (float rhs, const Quaternion& lhs);
Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
Vector3 operator * (const Quaternion& rotation, const Vector3& point);

Quaternion operator += (Quaternion& lhs, const Quaternion& rhs);
Quaternion operator -= (Quaternion& lhs, const Quaternion& rhs);
Quaternion operator *= (Quaternion& lhs, float rhs);
Quaternion operator *= (Quaternion& lhs, const Quaternion& rhs);

bool operator == (const Quaternion& lhs, const Quaternion& rhs);
bool operator != (const Quaternion& lhs, const Quaternion& rhs);

#endif
