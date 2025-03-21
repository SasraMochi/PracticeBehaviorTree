#include "Vector3.h"
#include "Quaternion.h"
#include "Mathf.h"
#include <cmath>
#include <limits>
#include <algorithm>

const float kEpsilon{ 1e-05f };
const float kEpsilonNormalSqrt{ 1e-15f };

// �R���X�g���N�^
Vector3::Vector3(float x, float y, float z) :
	x{ x }, y{ y }, z{ z } {
}

// �R���X�g���N�^
Vector3::Vector3(float x, float y) :
	Vector3{ x, y, 0.0f } {
}

// �x�N�g���̒���
float Vector3::magnitude() const {
	return std::sqrt(sqr_magnitude());
}
// magnitude �� 1 �Ƃ����x�N�g��
Vector3 Vector3::normalized() const {
	return normalize(*this);
}

// �x�N�g����2��̒���
float Vector3::sqr_magnitude() const {
	return dot(*this, *this);
}

// [0]��[1]���g�p���āAx��y�����ɃA�N�Z�X
float Vector3::operator [] (int index) const {
	return (index == 0) ? x : (index == 1) ? y : z;
}

// [0]��[1]���g�p���āAx��y�����ɃA�N�Z�X
float& Vector3::operator [] (int index) {
	return (index == 0) ? x : (index == 1) ? y : z;
}

// Returns true if the given vector is exactly equal to this vector.
bool Vector3::equals(const Vector3& other) const {
	return x == other.x && y == other.y && z == other.z;
}

// magnitude �� 1 �Ƃ����x�N�g�����쐬���܂�
void Vector3::normalize() {
	*this = normalize(*this);
}

// 2�̃x�N�g���̊e��������Z���܂�
void Vector3::scale(const Vector3& v) {
	*this = scale(*this, v);
}

// ������ Vector3 �� x�Ay�Az �̐�����ݒ肵�܂�
void Vector3::set(float new_x, float new_y, float new_z) {
	x = new_x; y = new_y; z = new_z;
}

// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
std::string Vector3::to_string() const {
	return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}

// 2�_�ԁifrom �� to�j�̊p�x��Ԃ��܂�
float Vector3::angle(const Vector3& from, const Vector3& to) {
	// sqrt(a) * sqrt(b) = sqrt(a * b) -- valid for real numbers
	float denominator = std::sqrt(from.sqr_magnitude() * to.sqr_magnitude());
	if (denominator < kEpsilonNormalSqrt)
		return 0.0f;
	float cos = Mathf::clamp(dot(from, to) / denominator, -1.0f, 1.0f);
	return Mathf::rad_to_deg() * std::acos(cos);
}

// �傫����max_length�܂łɐ������� vector �̃R�s�[��Ԃ��܂�
Vector3 Vector3::clamp_magnitude(const Vector3& vector, float max_length) {
	if (vector.sqr_magnitude() > max_length * max_length)
		return vector.normalized() * max_length;
	return vector;
}

// 2�̃x�N�g���̊O��
Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs) {
	return Vector3{ lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
}

// a �� b �̊Ԃ̋�����Ԃ��܂�
float Vector3::distance(const Vector3& a, const Vector3& b) {
	return (a - b).magnitude();
}

// 2�̃x�N�g���̓���
float Vector3::dot(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float t) {
	return lerp_unclamped(a, b, Mathf::clamp01(t));
}

// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
Vector3 Vector3::lerp_unclamped(const Vector3& a, const Vector3& b, float t) {
	return a + (b - a) * t;
}

// 2�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬���܂�
Vector3 Vector3::max(const Vector3& lhs, const Vector3& rhs) {
	return Vector3{ std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z) };
}

// 2�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬���܂�
Vector3 Vector3::min(const Vector3& lhs, const Vector3& rhs) {
	return Vector3{ std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z) };
}

// ���K������
Vector3 Vector3::normalize(const Vector3& value) {
	float mag = value.magnitude();
	if (mag > kEpsilon)
		return value / mag;
	return zero();
}

// �x�N�g�������K�����ꑼ�̃x�N�g���ƒ�������悤�ɂ��܂�
void Vector3::ortho_normalize(Vector3& normal, Vector3& tangent, Vector3& binormal) {
	normal.normalize();
	if (normal.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		normal = Vector3{ 1.0f, 0.0f, 0.0f };
	}
	Vector3 bn = cross(normal, tangent);
	if (binormal.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		tangent = cross(Vector3{ 0.0f, 0.0f, 1.0f }, normal);
	}
	if (tangent.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		tangent = cross(Vector3{ 1.0f, 0.0f, 0.0f }, normal);
	}
	bn = cross(normal, tangent);
	bn.normalize();
	tangent = cross(bn, normal);
	binormal = (Vector3::dot(bn, binormal) < 0.0f) ? -bn : bn;
}

// 2�̃x�N�g���̊e��������Z���܂�
Vector3 Vector3::scale(const Vector3& a, const Vector3& b) {
	return Vector3{ a.x * b.x, a.y * b.y, a.z * b.z };
}

// �x�N�g����ʂ̃x�N�g���ɓ��e���܂�
Vector3 Vector3::project(const Vector3& vector, const Vector3& on_normal) {
	float sqr_mag = on_normal.sqr_magnitude();
	if (sqr_mag < kEpsilon)
		return zero();
	return on_normal * dot(vector, on_normal) / sqr_mag;
}

// ���ʂɐ����Ȗ@���x�N�g���ɂ���Ē�`����镽�ʏ�Ƀx�N�g�����ˉe���܂�
Vector3 Vector3::project_on_plane(const Vector3& vector, const Vector3& planeNormal) {
	return vector - project(vector, planeNormal);
}

// �@���Œ�`���ꂽ���ʂŃx�N�g���𔽎˂��܂�
Vector3 Vector3::reflect(const Vector3& inDirection, const Vector3& inNormal) {
	return -2.0f * dot(inNormal, inDirection) * inNormal + inDirection;
}

// ���݂̈ʒu current ���� target �Ɍ����ăx�N�g������]���܂��B
Vector3 Vector3::rotate_towards(const Vector3& current, const Vector3& target, float max_radian_delta, float max_magnitude_delta) {
	// �p�x�ɕϊ�
	float max_degree_delta = max_radian_delta * Mathf::rad_to_deg();
	// �x�N�g���̒��������߂�
	float current_mag = current.magnitude();
	float target_mag = target.magnitude();
	// �x�N�g���̐��K��
	Vector3 current_normal = current / current_mag;
	Vector3 target_normal = target / target_mag;
	// 2�x�N�g���Ԃ̊p�x�����߂�
	float angle = Vector3::angle(current_normal, target_normal);
	// ��]�̎����v�Z
	Vector3 axis = Vector3::cross(current_normal, target_normal);
	// ��]�̎����ł��Ȃ������ꍇ�̕␳
	if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		axis = Vector3::cross(Vector3{ 0.0f, 0.0f, 1.0f }, current);
		if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
			axis = Vector3::cross(Vector3{ 1.0f, 0.0f, 0.0f }, current);
		}
	}
	// �p�x�̕�Ԃ�����
	float angle_towards = Mathf::move_towards(0.0f, angle, max_degree_delta);
	// �����̕�Ԃ�����
	float magnitude_toward = Mathf::move_towards(current_mag, target_mag, max_magnitude_delta);
	return Quaternion::angle_axis(angle_towards, axis) * current_normal * magnitude_toward;
}

// ���݂̈ʒu current ���� target �Ɍ����Ĉړ����܂�
Vector3 Vector3::move_towards(const Vector3& current, const Vector3& target, float max_distance_delta) {
	Vector3 to_vector = target - current;
	float dist = to_vector.magnitude();
	if (dist <= max_distance_delta || dist < kEpsilon)
		return target;
	return current + to_vector / dist * max_distance_delta;
}

// 2�_�ԁifrom �� to�j�̕����t���p�x��Ԃ��܂�
float Vector3::signed_angle(const Vector3& from, const Vector3& to, const Vector3& axis) {
	float unsigned_angle = angle(from, to);
	float sign = Mathf::sign(dot(axis, cross(from, to)));
	return unsigned_angle * sign;
}

// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
Vector3 Vector3::slerp(const Vector3& a, const Vector3& b, float t) {
	return slerp_unclamped(a, b, Mathf::clamp01(t));
}

// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
Vector3 Vector3::slerp_unclamped(const Vector3& a, const Vector3& b, float t) {
	// ��]�̎����v�Z
	Vector3 axis = Vector3::cross(a, b);
	// ��]�̎����ł��Ȃ������ꍇ�̕␳
	if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		axis = Vector3::cross(Vector3{ 0.0f, 0.0f, 1.0f }, a);
		if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
			axis = Vector3::cross(Vector3{ 1.0f, 0.0f, 0.0f }, a);
		}
	}
	// ��]�̕�Ԃ��s��
	return Quaternion::angle_axis(angle(a, b) * t, axis) * a.normalized() * Mathf::lerp_unclamped(a.magnitude(), b.magnitude(), t);
}

// �ړI�n�Ɍ������Ď��Ԃ̌o�߂ƂƂ��ɏ��X�Ƀx�N�g����ω������܂�
Vector3 Vector3::smooth_damp(const Vector3& current, const Vector3& target, Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime) {
	smoothTime = std::max(0.0001f, smoothTime);
	float omega = 2.0f / smoothTime;

	float x = omega * deltaTime;
	float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
	Vector3 change = current - target;
	Vector3 originalTo = target;

	float maxChange = maxSpeed * smoothTime;
	change = clamp_magnitude(change, maxChange);

	Vector3 temp = (currentVelocity + omega * change) * deltaTime;
	currentVelocity = (currentVelocity - omega * temp) * exp;
	Vector3 output = (current - change) + (change + temp) * exp;

	if (Vector3::dot(originalTo - current, output - originalTo) > 0.0f) {
		output = originalTo;
		currentVelocity = (output - originalTo) / deltaTime;
	}
	return output;
}

// Vector3(0, 0, 0) �Ɠ����Ӗ�
Vector3 Vector3::zero() {
	return Vector3{ 0.0, 0.0f, 0.0f };
}

// Vector3(1, 1, 1) �Ɠ����Ӗ�
Vector3 Vector3::one() {
	return Vector3{ 1.0, 1.0f, 1.0f };
}

// Vector3(0, 1, 0) �Ɠ����Ӗ�
Vector3 Vector3::up() {
	return Vector3{ 0.0, 1.0f, 0.0f };
}

// Vector3(0, -1, 0) �Ɠ����Ӗ�
Vector3 Vector3::down() {
	return Vector3{ 0.0, -1.0f, 0.0f };
}

// Vector3(-1, 0, 0) �Ɠ����Ӗ�
Vector3 Vector3::left() {
	return Vector3{ -1.0, 0.0f, 0.0f };
}

// Vector3(1, 0, 0) �Ɠ����Ӗ�
Vector3 Vector3::right() {
	return Vector3{ 1.0, 0.0f, 0.0f };
}

// Vector3(0, 0, 1) �Ɠ����Ӗ�
Vector3 Vector3::forward() {
	return Vector3{ 0.0, 0.0f, 1.0f };
}

// Vector3(0, 0, -1) �Ɠ����Ӗ�
Vector3 Vector3::back() {
	return Vector3{ 0.0, 0.0f, -1.0f };
}

// ���̖�����
Vector3 Vector3::positive_infinity() {
	return Vector3{ std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() };
}

// ���̖�����
Vector3 Vector3::negative_infinity() {
	return -positive_infinity();
}

// ������Z�q�I�[�o�[���[�h
Vector3& operator += (Vector3& lhs, const Vector3& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector3& operator -= (Vector3& lhs, const Vector3& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector3& operator *= (Vector3& lhs, float rhs) {
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector3& operator /= (Vector3& lhs, float rhs) {
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

// Adds two vectors.
Vector3 operator+(const Vector3& a, const Vector3& b) {
	return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

// Subtracts one vector from another.
Vector3 operator-(const Vector3& a, const Vector3& b) {
	return Vector3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

// Negates a vector.
Vector3 operator-(const Vector3& a) {
	return Vector3{ -a.x, -a.y, -a.z };
}

// Multiplies a vector by a number.
Vector3 operator*(const Vector3& a, float d) {
	return Vector3{ a.x * d, a.y * d, a.z * d };
}

// Multiplies a vector by a number.
Vector3 operator * (float d, const Vector3& a) {
	return a * d;
}

// Divides a vector by a number.
Vector3 operator/(const Vector3& a, float d) {
	return a * (1.0f / d);
}

// Returns true if the vectors are equal.
bool operator == (const Vector3& lhs, const Vector3& rhs) {
	// Returns false in the presence of NaN values.
	return (lhs - rhs).sqr_magnitude() < (kEpsilon * kEpsilon);
}

// Returns true if vectors are different.
bool operator != (const Vector3& lhs, const Vector3& rhs) {
	// Returns true in the presence of NaN values.
	return !(lhs == rhs);
}
