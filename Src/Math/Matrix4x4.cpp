#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Mathf.h"
#include <iostream>

// コンストラクタ
Matrix4x4::Matrix4x4(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44) {
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
	m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
}

// ゼロ行列
Matrix4x4 Matrix4x4::zero() {
	return Matrix4x4{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};
}

// 単位行列
Matrix4x4 Matrix4x4::identity() {
	return Matrix4x4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

// 拡大縮小
Matrix4x4 Matrix4x4::scale(const Vector3& vector) {
	return Matrix4x4{
		vector.x, 0.0f, 0.0f, 0.0f,
		0.0f, vector.y, 0.0f, 0.0f,
		0.0f, 0.0f, vector.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

// x軸回転
Matrix4x4 Matrix4x4::rotate_x(float degree) {
	float rad = degree * Mathf::deg_to_rad();
	float cos = std::cos(rad);
	float sin = std::sin(rad);
	return Matrix4x4{
				1.0f,  0.0f, 0.0f, 0.0f,
		0.0f,   cos,  sin, 0.0f,
		0.0f,  -sin,  cos, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f
	};
}

// y軸回転
Matrix4x4 Matrix4x4::rotate_y(float degree) {
	float rad = degree * Mathf::deg_to_rad();
	float cos = std::cos(rad);
	float sin = std::sin(rad);
	return Matrix4x4{
		 cos, 0.0f, -sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		 sin, 0.0f,  cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

// z軸回転
Matrix4x4 Matrix4x4::rotate_z(float degree) {
	float rad = degree * Mathf::deg_to_rad();
	float cos = std::cos(rad);
	float sin = std::sin(rad);
	return Matrix4x4{
		 cos,  sin, 0.0f, 0.0f,
		-sin,  cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

// 回転
Matrix4x4 Matrix4x4::rotate(const Quaternion& rotate) {
	float xx = rotate.x * rotate.x * 2.0f;
	float yy = rotate.y * rotate.y * 2.0f;
	float zz = rotate.z * rotate.z * 2.0f;
	float xy = rotate.x * rotate.y * 2.0f;
	float xz = rotate.x * rotate.z * 2.0f;
	float yz = rotate.y * rotate.z * 2.0f;
	float wx = rotate.w * rotate.x * 2.0f;
	float wy = rotate.w * rotate.y * 2.0f;
	float wz = rotate.w * rotate.z * 2.0f;
	return Matrix4x4{
		1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
		xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
		xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
}

// 平行移動
Matrix4x4 Matrix4x4::translate(const Vector3& position) {
	return  Matrix4x4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
				position.x, position.y, position.z, 1.0f
	};
}

// この行列を移動、回転やスケーリングする行列に設定します。
Matrix4x4 Matrix4x4::TRS(const Vector3& p, const Quaternion& q, const Vector3& s) {
	Matrix4x4 result = rotate(q);
	result.m[0][0] *= s.x; result.m[0][1] *= s.x; result.m[0][2] *= s.x;
	result.m[1][0] *= s.y; result.m[1][1] *= s.y; result.m[1][2] *= s.y;
	result.m[2][0] *= s.z; result.m[2][1] *= s.z; result.m[2][2] *= s.z;
	result.m[3][0] = p.x; result.m[3][1] = p.y; result.m[3][2] = p.z;
	return result;
}

// 視野変換行列 (DirectX 左手座標系)
Matrix4x4 Matrix4x4::look_at(const Vector3& eye, const Vector3& at, const Vector3& up) {
	Vector3 z = (at - eye).normalized();
	Vector3 x = Vector3::cross(up, z).normalized();
	Vector3 y = Vector3::cross(z, x);
	return Matrix4x4{
		x.x, y.x, z.x, 0.0f,
		x.y, y.y, z.y, 0.0f,
		x.z, y.z, z.z, 0.0f,
		-Vector3::dot(eye, x), -Vector3::dot(eye, y), -Vector3::dot(eye, z), 1.0f
	};
}

// 透視変換行列 (DirectX 左手座標系)
Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float zn, float zf) {
	float f = 1.0f / std::tan(fov / 2.0f * Mathf::deg_to_rad());
	return Matrix4x4{
		f / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, f,    0.0f, 0.0f,
		0.0f, 0.0f, zf / (zf - zn), 1.0f,
		0.0f, 0.0f, (-zn * zf) / (zf - zn), 0.0f
	};
}

// 座標変換（通常）
Vector3 Matrix4x4::multiply_point(const Vector3& point) const {
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
	float w = point.x * m[0][3] + point.y * m[1][3] + point.z * m[2][3] + m[3][3];
	return Vector3{ x / w, y / w, z / w };
}

// 座標変換（高速）
Vector3 Matrix4x4::multiply_point4x3(const Vector3& point) const {
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
	return Vector3{ x, y, z };
}

// ベクトル変換（平行移動なし）
Vector3 Matrix4x4::multiply_vector(const Vector3& point) const {
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2];
	return Vector3{ x, y, z };
}

// スケール値を取得
Vector3 Matrix4x4::scale() const {
	float sx = Vector3{ m[0][0], m[0][1], m[0][2] }.magnitude();
	float sy = Vector3{ m[1][0], m[1][1], m[1][2] }.magnitude();
	float sz = Vector3{ m[2][0], m[2][1], m[2][2] }.magnitude();
	return Vector3{ sx, sy, sz };
}

// 回転の取得
Quaternion Matrix4x4::rotation() const {
	Quaternion result;
	float tr = m[0][0] + m[1][1] + m[2][2] + 1.0f;
	if (tr >= 1.0f) {
		float fourD = 2.0f * std::sqrt(tr);
		result.x = (m[1][2] - m[2][1]) / fourD;
		result.y = (m[2][0] - m[0][2]) / fourD;
		result.z = (m[0][1] - m[1][0]) / fourD;
		result.w = fourD / 4.0f;
		return result;
	}
	int i = 0;
	if (m[0][0] <= m[1][1]) {
		i = 1;
	}
	if (m[2][2] > m[i][i]) {
		i = 2;
	}
	int j = (i + 1) % 3;
	int k = (j + 1) % 3;
	tr = m[i][i] - m[j][j] - m[k][k] + 1.0f;
	float fourD = 2.0f * std::sqrt(tr);
	result[i] = fourD / 4.0f;
	result[j] = (m[j][i] + m[i][j]) / fourD;
	result[k] = (m[k][i] + m[i][k]) / fourD;
	result[3] = (m[j][k] - m[k][j]) / fourD;
	return result;
}

// 前方向ベクトルを取得
Vector3 Matrix4x4::forward() const {
	return Vector3{ m[2][0], m[2][1], m[2][2] }.normalized();
}

// 上方向ベクトルを取得
Vector3 Matrix4x4::up() const {
	return Vector3{ m[1][0], m[1][1], m[1][2] }.normalized();
}

// 右方向ベクトルを取得
Vector3 Matrix4x4::right() const {
	return Vector3{ m[0][0], m[0][1], m[0][2] }.normalized();
}

// 座標を取得
Vector3 Matrix4x4::position() const {
	return Vector3{ m[3][0], m[3][1], m[3][2] };
}

// この行列の逆行列。(Read Only)
Matrix4x4 Matrix4x4::inverse() const {
	float a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	float a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
	float a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
	float a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	float a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
	float a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
	float b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
	float b1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
	float b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
	float b3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
	float b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
	float b5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
	float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
	if (det == 0.0f) {
		return *this; // 逆行列が存在しない！
	}
	float invDet = 1.0f / det;
	return Matrix4x4{
		(m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3) * invDet,
		(-m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3) * invDet,
		(m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3) * invDet,
		(-m[2][1] * a5 + m[2][2] * a4 - m[2][3] * a3) * invDet,
		(-m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1) * invDet,
		(m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1) * invDet,
		(-m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1) * invDet,
		(m[2][0] * a5 - m[2][2] * a2 + m[2][3] * a1) * invDet,
		(m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0) * invDet,
		(-m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0) * invDet,
		(m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0) * invDet,
		(-m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0) * invDet,
		(-m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0) * invDet,
		(m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0) * invDet,
		(-m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0) * invDet,
		(m[2][0] * a3 - m[2][1] * a1 + m[2][2] * a0) * invDet
	};
}

// この行列の転置行列
Matrix4x4 Matrix4x4::transpose() const {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m[j][i];
		}
	}
	return result;
}

// この行列を移動、回転やスケーリングする行列に設定します。
void Matrix4x4::set_TRS(const Vector3& p, const Quaternion& q, const Vector3& s) {
	*this = TRS(p, q, s);
}

// 行列の加算 
Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = lhs.m[i][j] + rhs.m[i][j];
		}
	}
	return result;
}

// 行列の減算 
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = lhs.m[i][j] - rhs.m[i][j];
		}
	}
	return result;
}

// 行列のスカラー倍
Matrix4x4 operator * (const Matrix4x4& lhs, float rhs) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = lhs.m[i][j] * rhs;
		}
	}
	return result;
}

// 行列のスカラー倍
Matrix4x4 operator * (float lhs, const Matrix4x4& rhs) {
	return rhs * lhs;
}

// 行列の乗算
Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
			}
		}
	}
	return result;
}

// 行列とベクトルの積(multiply_point)
Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs) {
	return rhs.multiply_point(lhs);
}

// 行列の加算 
Matrix4x4& operator += (Matrix4x4& lhs, const Matrix4x4& rhs) {
	return lhs = lhs + rhs;
}

// 行列の減算 
Matrix4x4& operator -= (Matrix4x4& lhs, const Matrix4x4& rhs) {
	return lhs = lhs - rhs;
}

// 行列のスカラー倍
Matrix4x4& operator *= (Matrix4x4& lhs, float rhs) {
	return lhs = lhs * rhs;
}

// 行列の乗算
Matrix4x4& operator *= (Matrix4x4& lhs, const Matrix4x4& rhs) {
	return lhs = lhs * rhs;
}

// 行列の出力
std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			lhs << rhs.m[i][j];
			if (j < (4 - 1)) {
				lhs << " ";
			}
		}
		lhs << std::endl;
	}
	return lhs;
}