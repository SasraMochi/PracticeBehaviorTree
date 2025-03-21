#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <iosfwd> // ostreamの先行宣言

struct Vector3;
struct Quaternion;

// 行列
struct Matrix4x4 {
	float m[4][4]{};
	// コンストラクタ
	Matrix4x4() = default;
	// コンストラクタ
	Matrix4x4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
	// ゼロ行列
	static Matrix4x4 zero();
	// 単位行列
	static Matrix4x4 identity();
	// 拡大縮小
	static Matrix4x4 scale(const Vector3& vector);
	// x軸回転
	static Matrix4x4 rotate_x(float degree);
	// y軸回転
	static Matrix4x4 rotate_y(float degree);
	// z軸回転
	static Matrix4x4 rotate_z(float degree);
	// 回転
	static Matrix4x4 rotate(const Quaternion& q);
	// 平行移動
	static Matrix4x4 translate(const Vector3& position);
	// この行列を移動、回転やスケーリングする行列に設定します。
	static Matrix4x4 TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);

	// 視野変換行列
	static Matrix4x4 look_at(const Vector3& eye, const Vector3& at, const Vector3& up);
	// 透視変換行列
	static Matrix4x4 perspective(float fov, float aspect, float zn, float zf);

	// 座標変換（通常）
	Vector3 multiply_point(const Vector3& point) const;
	// 座標変換（高速）
	Vector3 multiply_point4x3(const Vector3& point) const;
	// ベクトル変換（平行移動なし）
	Vector3 multiply_vector(const Vector3& point) const;

	// スケール値を取得
	Vector3 scale() const;
	// 座標を取得
	Vector3 position() const;
	// 回転の取得
	Quaternion rotation() const;
	// 前方向ベクトルを取得
	Vector3 forward() const;
	// 上方向ベクトルを取得
	Vector3 up() const;
	// 右方向ベクトルを取得
	Vector3 right() const;

	// この行列の逆行列。(Read Only)
	Matrix4x4 inverse() const;
	// この行列の転置行列
	Matrix4x4 transpose() const;
	// この行列を移動、回転やスケーリングする行列に設定します。
	void set_TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);
};

// 行列の加算 
Matrix4x4 operator + (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列の減算 
Matrix4x4 operator - (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列のスカラー倍
Matrix4x4 operator * (const Matrix4x4& lhs, float rhs);
// 行列のスカラー倍
Matrix4x4 operator * (float lhs, const Matrix4x4& rhs);
// 行列の乗算
Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列とベクトルの積(multiply_point)
Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs);

// 行列の加算 
Matrix4x4& operator += (Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列の減算 
Matrix4x4& operator -= (Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列のスカラー倍
Matrix4x4& operator *= (Matrix4x4& lhs, float rhs);
// 行列の乗算
Matrix4x4& operator *= (Matrix4x4& lhs, const Matrix4x4& rhs);

// 行列の出力
std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs);

#endif
