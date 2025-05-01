#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <string>

// 2Dベクトルクラス
class Vector2 {
public:
    // ===== メンバ変数 =====
    float x{ 0.0f }; // x成分
    float y{ 0.0f }; // y成分

    // ===== コンストラクタ =====
    Vector2() = default; // デフォルトコンストラクタ
    Vector2(float x, float y); // x, yを指定するコンストラクタ

    // ===== 静的メソッド =====
    static Vector2 zero();       // (0, 0) ベクトル
    static Vector2 one();        // (1, 1) ベクトル
    static Vector2 up();         // (0, 1) ベクトル
    static Vector2 down();       // (0, -1) ベクトル
    static Vector2 left();       // (-1, 0) ベクトル
    static Vector2 right();      // (1, 0) ベクトル

    // ===== インスタンスメソッド =====
    int int_x() const;           // x成分をint型で取得
    int int_y() const;           // y成分をint型で取得
    float magnitude() const;     // ベクトルの長さ
    Vector2 normalized() const;  // 正規化されたベクトル
    float sqr_magnitude() const; // ベクトルの長さの2乗
    float operator[](int index) const; // インデックスアクセス（読み取り）
    float& operator[](int index);      // インデックスアクセス（書き込み）
    bool equals(const Vector2& other); // ベクトルの等価比較
    void normalize();                  // ベクトルを正規化
    void set(float x, float y);        // x, y成分を設定
    std::string to_string() const;     // ベクトルを文字列化

    // ===== 静的ユーティリティメソッド =====
    static float angle(const Vector2& from, const Vector2& to);
    static Vector2 clamp_magnitude(const Vector2& vector, float max_length);
    static float distance(const Vector2& a, const Vector2& b);
    static float dot(const Vector2& lhs, const Vector2& rhs);
    static Vector2 lerp(const Vector2& a, const Vector2& b, float t);
    static Vector2 lerp_unclamped(const Vector2& a, const Vector2& b, float t);
    static Vector2 max_value(const Vector2& lhs, const Vector2& rhs);
    static Vector2 min_value(const Vector2& lhs, const Vector2& rhs);
    static Vector2 move_towards(const Vector2& current, const Vector2& target, float max_distance_delta);
    static Vector2 perpendicular(const Vector2& inDirection);
    static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
    static Vector2 scale(const Vector2& a, const Vector2& b);
    static float signed_angle(const Vector2& from, const Vector2& to);
    Vector2 smooth_damp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smooth_time, float max_speed, float delta_time);

    // ===== 演算子オーバーロード =====
    friend Vector2 operator-(const Vector2& v);
    friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
    friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
    friend Vector2& operator*=(Vector2& lhs, float rhs);
    friend Vector2& operator/=(Vector2& lhs, float rhs);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator*(const Vector2& lhs, float rhs);
    friend Vector2 operator*(float lhs, const Vector2& rhs);
    friend Vector2 operator/(const Vector2& lhs, float rhs);
    friend bool operator==(const Vector2& lhs, const Vector2& rhs);
    friend bool operator!=(const Vector2& lhs, const Vector2& rhs);
};

#endif // VECTOR2_H_
