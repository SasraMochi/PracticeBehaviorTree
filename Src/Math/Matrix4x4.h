#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <iosfwd> // ostream�̐�s�錾

struct Vector3;
struct Quaternion;

// �s��
struct Matrix4x4 {
	float m[4][4]{};
	// �R���X�g���N�^
	Matrix4x4() = default;
	// �R���X�g���N�^
	Matrix4x4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
	// �[���s��
	static Matrix4x4 zero();
	// �P�ʍs��
	static Matrix4x4 identity();
	// �g��k��
	static Matrix4x4 scale(const Vector3& vector);
	// x����]
	static Matrix4x4 rotate_x(float degree);
	// y����]
	static Matrix4x4 rotate_y(float degree);
	// z����]
	static Matrix4x4 rotate_z(float degree);
	// ��]
	static Matrix4x4 rotate(const Quaternion& q);
	// ���s�ړ�
	static Matrix4x4 translate(const Vector3& position);
	// ���̍s����ړ��A��]��X�P�[�����O����s��ɐݒ肵�܂��B
	static Matrix4x4 TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);

	// ����ϊ��s��
	static Matrix4x4 look_at(const Vector3& eye, const Vector3& at, const Vector3& up);
	// �����ϊ��s��
	static Matrix4x4 perspective(float fov, float aspect, float zn, float zf);

	// ���W�ϊ��i�ʏ�j
	Vector3 multiply_point(const Vector3& point) const;
	// ���W�ϊ��i�����j
	Vector3 multiply_point4x3(const Vector3& point) const;
	// �x�N�g���ϊ��i���s�ړ��Ȃ��j
	Vector3 multiply_vector(const Vector3& point) const;

	// �X�P�[���l���擾
	Vector3 scale() const;
	// ���W���擾
	Vector3 position() const;
	// ��]�̎擾
	Quaternion rotation() const;
	// �O�����x�N�g�����擾
	Vector3 forward() const;
	// ������x�N�g�����擾
	Vector3 up() const;
	// �E�����x�N�g�����擾
	Vector3 right() const;

	// ���̍s��̋t�s��B(Read Only)
	Matrix4x4 inverse() const;
	// ���̍s��̓]�u�s��
	Matrix4x4 transpose() const;
	// ���̍s����ړ��A��]��X�P�[�����O����s��ɐݒ肵�܂��B
	void set_TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);
};

// �s��̉��Z 
Matrix4x4 operator + (const Matrix4x4& lhs, const Matrix4x4& rhs);
// �s��̌��Z 
Matrix4x4 operator - (const Matrix4x4& lhs, const Matrix4x4& rhs);
// �s��̃X�J���[�{
Matrix4x4 operator * (const Matrix4x4& lhs, float rhs);
// �s��̃X�J���[�{
Matrix4x4 operator * (float lhs, const Matrix4x4& rhs);
// �s��̏�Z
Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs);
// �s��ƃx�N�g���̐�(multiply_point)
Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs);

// �s��̉��Z 
Matrix4x4& operator += (Matrix4x4& lhs, const Matrix4x4& rhs);
// �s��̌��Z 
Matrix4x4& operator -= (Matrix4x4& lhs, const Matrix4x4& rhs);
// �s��̃X�J���[�{
Matrix4x4& operator *= (Matrix4x4& lhs, float rhs);
// �s��̏�Z
Matrix4x4& operator *= (Matrix4x4& lhs, const Matrix4x4& rhs);

// �s��̏o��
std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs);

#endif
