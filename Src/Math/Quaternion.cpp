#include "Quaternion.h"
#include "Mathf.h"
#include <algorithm>

const float kEpsilon{ 1e-05f };

inline bool is_equal_using_dot(float dot);
inline Vector3 internal_make_positive(Vector3 euler);

// コンストラクタ
Quaternion::Quaternion(float x, float y, float z, float w) :
	x{ x }, y{ y }, z{ z }, w{ w } {
}

// 単位クォータニオン
Quaternion Quaternion::identity() {
	return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

// 回転をオイラー角の値で返します
Vector3 Quaternion::euler_angles() const {
	Vector3 ax = *this * Vector3{ 1.0f, 0.0f, 0.0f };
	Vector3 ay = *this * Vector3{ 0.0f, 1.0f, 0.0f };
	Vector3 az = *this * Vector3{ 0.0f, 0.0f, 1.0f };
	Vector3 result = Vector3(0.0f, 0.0f, 0.0f);
	if (az.y < 1.0f) {
		if (az.y > -1.0f) {
			result.x = std::asin(-az.y);
			result.y = std::atan2(az.x, az.z);
			result.z = std::atan2(ax.y, ay.y);
		}
		else {
			// Not a unique solution.
			result.x = Mathf::pi() / 2.0f;
			result.y = -std::atan2(-ay.x, ax.x);
			result.z = 0.0f;
		}
	}
	else {
		// Not a unique solution.
		result.x = -Mathf::pi() / 2.0f;
		result.y = std::atan2(-ay.x, ax.x);
		result.z = 0.0f;
	}
	return internal_make_positive(result * Mathf::rad_to_deg());
}

// 回転をオイラー角の値で設定します
void Quaternion::euler_angles(const Vector3& value) {
	*this = euler(value);
}

// 正規化
Quaternion Quaternion::normalized() const {
	return normalize(*this);
}

// [0] や[1] を使用して x や y 成分にアクセスします
float Quaternion::operator[](int index) const {
	return (index == 0) ? x : (index == 2) ? y : (index == 3) ? z : w;
}
float& Quaternion::operator[](int index) {
	return (index == 0) ? x : (index == 2) ? y : (index == 3) ? z : w;
}

// 既存の Quaternion に x、y、z、w の成分を設定します
void Quaternion::set(float newX, float newY, float newZ, float newW) {
	x = newX; y = newY;  z = newZ; w = newW;
}

// fromDirection から toDirection への回転を作成します
void Quaternion::set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection) {
	*this = from_to_rotation(fromDirection, toDirection);
}

// 指定された forward と upwards 方向に回転します
void Quaternion::set_look_rotation(const Vector3& view, const Vector3& up) {
	*this = look_rotation(view, up);
}

// 回転を座標に対する角度の値 (AngleAxis) に変換します。
void Quaternion::to_angle_axis(float& angle, Vector3& axis) {
	float a = std::acos(w);
	float s = std::sin(a);
	angle = a * 2.0f * Mathf::rad_to_deg();
	if (s > kEpsilon) {
		axis = Vector3{ x, y, z } *(1.0f / s);
	}
	else {
		axis = Vector3{ 1.0f, 0.0f, 0.0f };
		angle = 0.0f;
	}
}

// クォータ二オンの値を見やすくした文字列を返します。
std::string Quaternion::to_string() const {
	return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + ")";
}

// 2つの回転aとb間の角度を返します。
float Quaternion::angle(const Quaternion& a, const Quaternion& b) {
	float dot = Quaternion::dot(a, b);
	return is_equal_using_dot(dot) ? 0.0f : std::acos(std::min(std::abs(dot), 1.0f)) * 2.0f * Mathf::rad_to_deg();
}

// axis の周りを angle 度回転する回転を作成します。
Quaternion Quaternion::angle_axis(float angle, const Vector3& axis) {
	float rad = angle * 0.5f * Mathf::deg_to_rad();
	float s = std::sin(rad) / axis.magnitude();
	return Quaternion{ axis.x * s, axis.y * s, axis.z * s, std::cos(rad) };
}

// 2 つの回転の内積を返します
float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// z軸を中心にz度、x軸を中心にx度、y軸を中心にy度回転する回転を返します。
Quaternion Quaternion::euler(float x, float y, float z) {
	return euler(Vector3{ x, y, z });
}

// z軸を中心にz度、x軸を中心にx度、y軸を中心にy度回転する回転を返します。
Quaternion Quaternion::euler(const Vector3& euler) {
	Vector3 v = euler * Mathf::deg_to_rad();
	float c1 = std::cos(v.x * 0.5f);
	float c2 = std::cos(v.y * 0.5f);
	float c3 = std::cos(v.z * 0.5f);
	float s1 = std::sin(v.x * 0.5f);
	float s2 = std::sin(v.y * 0.5f);
	float s3 = std::sin(v.z * 0.5f);
	float x = s1 * c2 * c3 + c1 * s2 * s3;
	float y = c1 * s2 * c3 - s1 * c2 * s3;
	float z = c1 * c2 * s3 - s1 * s2 * c3;
	float w = c1 * c2 * c3 + s1 * s2 * s3;
	return Quaternion{ x, y, z, w };
}

// fromDirection から toDirection への回転を作成します。
Quaternion Quaternion::from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection) {
	// 2ベクトル間の角度を求める
	float angle = Vector3::angle(fromDirection, toDirection);
	if (angle < kEpsilon) {
		return identity();
	}
	// 回転の軸を計算
	Vector3 axis = Vector3::cross(fromDirection, toDirection);
	// 回転の軸ができなかった場合の補正
	if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		axis = Vector3::cross(Vector3{ 0.0f, 0.0f, 1.0f }, fromDirection);
		if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
			axis = Vector3::cross(Vector3{ 1.0f, 0.0f, 0.0f }, fromDirection);
		}
	}
	return angle_axis(angle, axis);
}

// 逆クォータニオンを返します
Quaternion Quaternion::inverse(const Quaternion& rotation) {
	return Quaternion{ -rotation.x, -rotation.y, -rotation.z, rotation.w };
}

// 指定された forward と upwards 方向に回転します
Quaternion Quaternion::look_rotation(const Vector3& view, const Vector3& up) {
	Vector3 forward = Vector3::normalize(view);
	if (forward.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		forward = Vector3{ 0.0f, 0.0f, 1.0f };
	}
	Vector3 right = Vector3::cross(up, forward);
	if (right.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		right = Vector3{ 1.0f, 0.0f, 0.0f };
	}
	Vector3 upwards = Vector3::cross(forward, right);
	upwards.normalize();
	right = Vector3::cross(upwards, forward);
	Quaternion result;
	float radicand = right.x + upwards.y + forward.z;
	if (radicand > 0.0f) {
		result.w = std::sqrt(1.0f + radicand) * 0.5f;
		float recip = 1.0f / (4.0f * result.w);
		result.x = (upwards.z - forward.y) * recip;
		result.y = (forward.x - right.z) * recip;
		result.z = (right.y - upwards.x) * recip;
	}
	else if (right.x >= upwards.y && right.x >= forward.z) {
		result.x = std::sqrt(1.0f + right.x - upwards.y - forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.x);
		result.w = (upwards.z - forward.y) * recip;
		result.z = (forward.x + right.z) * recip;
		result.y = (right.y + upwards.x) * recip;
	}
	else if (upwards.y > forward.z) {
		result.y = std::sqrt(1.0f - right.x + upwards.y - forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.y);
		result.z = (upwards.z + forward.y) * recip;
		result.w = (forward.x - right.z) * recip;
		result.x = (right.y + upwards.x) * recip;
	}
	else {
		result.z = std::sqrt(1.0f - right.x - upwards.y + forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.z);
		result.y = (upwards.z + forward.y) * recip;
		result.x = (forward.x + right.z) * recip;
		result.w = (right.y - upwards.x) * recip;
	}
	return result;
}

// 正規化したクォータニオンを返します
Quaternion Quaternion::normalize(const Quaternion& q) {
	float mag = std::sqrt(dot(q, q));
	if (mag < kEpsilon) {
		return Quaternion::identity();
	}
	return Quaternion{ q.x / mag, q.y / mag, q.z / mag, q.w / mag };
}

// from から to への回転を得ます
Quaternion Quaternion::rotate_towards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta) {
	float angle = Quaternion::angle(from, to);
	if (angle == 0.0f) return to;
	return slerp_unclamped(from, to, std::min(1.0f, maxDegreesDelta / angle));
}

// aとbの間をtで線形に補間します。パラメーターtは、[0, 1] の範囲です。
Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t) {
	return lerp_unclamped(a, b, Mathf::clamp01(t));
}

// aとbの間をtで球状に補間します。パラメーターtは、限られていません。
Quaternion Quaternion::lerp_unclamped(const Quaternion& a, const Quaternion& b, float t) {
	return (a * (1.0f - t) + b * t).normalized();
}

// aとbの間をtで球状に補間します。パラメーターtは、[0, 1] の範囲です。
Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t) {
	return slerp_unclamped(a, b, Mathf::clamp01(t));
}

// aとbの間をtで球状に補間します。パラメーターtは、限られていません。
Quaternion Quaternion::slerp_unclamped(const Quaternion& a, const Quaternion& b, float t) {
	float cos = dot(a, b);
	float sign = 1.0f;
	if (cos < 0.0f) {
		cos = -cos;
		sign = -1.0f;
	}
	float t0 = 1.0f - t;
	float t1 = t;
	if (cos < 0.999f) {
		float theta = std::acos(cos);
		t0 = std::sin(theta * t0) / std::sin(theta);
		t1 = std::sin(theta * t1) / std::sin(theta);
	}
	return ((a * t0) + (b * sign * t1)).normalized();
}

// 比較(完全に値が一致しているか？）
bool Quaternion::equals(const Quaternion& other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs) {
	return Quaternion{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
}

Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs) {
	return Quaternion{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
}

Quaternion operator * (const Quaternion& lhs, float rhs) {
	return Quaternion{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
}

Quaternion operator * (float rhs, const Quaternion& lhs) {
	return lhs * rhs;
}

Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs) {
	return Quaternion{
				lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z };
}

// Rotates the point /point/ with /rotation/.
Vector3 operator * (const Quaternion& rotation, const Vector3& point) {
	float x = rotation.x * 2.0f;
	float y = rotation.y * 2.0f;
	float z = rotation.z * 2.0f;
	float xx = rotation.x * x;
	float yy = rotation.y * y;
	float zz = rotation.z * z;
	float xy = rotation.x * y;
	float xz = rotation.x * z;
	float yz = rotation.y * z;
	float wx = rotation.w * x;
	float wy = rotation.w * y;
	float wz = rotation.w * z;
	Vector3 res;
	res.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;
	return res;
}

Quaternion operator+=(Quaternion& lhs, const Quaternion& rhs) {
	return lhs = lhs + rhs;
}

Quaternion operator-=(Quaternion& lhs, const Quaternion& rhs) {
	return lhs = lhs - rhs;
}

Quaternion operator*=(Quaternion& lhs, float rhs) {
	return lhs = lhs * rhs;
}

Quaternion operator*=(Quaternion& lhs, const Quaternion& rhs) {
	return lhs = lhs * rhs;
}

// Are two quaternions equal to each other?
bool operator == (const Quaternion& lhs, const Quaternion& rhs) {
	return is_equal_using_dot(Quaternion::dot(lhs, rhs));
}

// Are two quaternions different from each other?
bool operator != (const Quaternion& lhs, const Quaternion& rhs) {
	// Returns true in the presence of NaN values.
	return !(lhs == rhs);
}

// 0～360のプラスの角度に変換
inline Vector3 internal_make_positive(Vector3 euler) {
	float negative_flip = -0.0001f * Mathf::rad_to_deg();
	float positive_flip = 360.0f + negative_flip;

	if (euler.x < negative_flip)
		euler.x += 360.0f;
	else if (euler.x > positive_flip)
		euler.x -= 360.0f;

	if (euler.y < negative_flip)
		euler.y += 360.0f;
	else if (euler.y > positive_flip)
		euler.y -= 360.0f;

	if (euler.z < negative_flip)
		euler.z += 360.0f;
	else if (euler.z > positive_flip)
		euler.z -= 360.0f;

	return euler;
}

// 内積を比較する際に誤差を考慮
inline bool is_equal_using_dot(float dot) {
	// Returns false in the presence of NaN values.
	return dot > 1.0f - kEpsilon;
}