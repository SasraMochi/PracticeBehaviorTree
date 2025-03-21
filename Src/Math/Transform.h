#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include <list>

// トランスフォームクラス
class Transform {
public:
    // 座標系の指定
    enum class Space {
        Self,   // ローカル座標系
        World   // ワールド座標系
    };
    // コンストラクタ
    Transform() = default;
    // デストラクタ
    ~Transform();
    // ワールド空間の Transform の青軸を取得
    Vector3 forward() const;
    // ワールド空間の Transform の青軸を設定
    void forward(const Vector3& value);
    // ワールド空間の Transform の赤軸を取得
    Vector3 right() const;
    // ワールド空間の Transform の赤軸を設定
    void right(const Vector3& value);
    // ワールド空間の Transform の緑軸を取得
    Vector3 up() const;
    // ワールド空間の Transform の緑軸を設定
    void up(const Vector3& value);

    // オブジェクトのグローバルスケールを取得
    Vector3 lossy_scale() const;
    // ワールド空間の Transform の位置を取得
    Vector3 position() const;
    // ワールド空間の Transform の位置を設定
    void position(const Vector3& value);
    // Quaternion として保存されるワールド空間での Transform の回転を取得
    Quaternion rotation() const;
    // Quaternion として保存されるワールド空間での Transform の回転を設定
    void rotation(const Quaternion& value);
    // オイラー角としての角度を取得
    Vector3 euler_angles() const;
    // オイラー角としての角度を設定
    void euler_angles(const Vector3& value);

    // 対象の Transform を設定し、その方向へと向かせます
    void look_at(const Transform& target, const Vector3& world_up = Vector3{ 0.0f, 1.0f, 0.0f });
    void look_at(const Vector3& target, const Vector3& world_up = Vector3{ 0.0f, 1.0f, 0.0f });
    // Z 軸でeulers.z 度回転、X軸で euler.x 度回転、Y軸でeulers.y 度回転します(順番は説明した順)
    void rotate(const Vector3& eulers, Space relative_to = Space::Self);
    // axis 軸の周りに angle 度、回転します
    void rotate(const Vector3& axis, float angle, Space relative_to = Space::Self);
    // ワールド座標の point を中心とした軸(axis)で angle 度回転させます
    void rotate_around(const Vector3& point, const Vector3& axis, float angle);

    // translation の方向と距離に移動します
    void translate(const Vector3& translation, Space relative_to = Space::Self);

    // ローカル座標からワールド座標へ変換した行列
    Matrix4x4 local_to_world_matrix() const;
    // ワールド座標からローカル座標へ変換した行列
    Matrix4x4 world_to_local_matrix() const;

    // ローカル空間からワールド空間へ position を変換します。(スケール・回転・平行移動）
    Vector3 transform_point(const Vector3& position) const;
    // ローカル空間からワールド空間へ vector を変換します。(スケール・回転）
    Vector3 transform_vector(const Vector3& vector) const;
    // ローカル空間からワールド空間へ direction を変換します(回転）
    Vector3 transform_direction(const Vector3& direction) const;

    // ワールド空間からローカル空間へ position を変換します
    Vector3 inverse_transform_point(const Vector3& position) const;
    // ワールド空間からローカル空間へ vector を変換します
    Vector3 inverse_transform_vector(const Vector3& vector) const;
    // ワールド空間からローカル空間へ direction を変換します
    Vector3 inverse_transform_direction(const Vector3& direction) const;

    // Transform の親を設定
    void parent(Transform* parent);
    // Transform の親を取得
    Transform* parent() const;
    // Transform の親を設定
    void set_parent(Transform* parent, bool world_position_stays = true);

    // 親の Transform オブジェクトから見た相対的なスケールを取得
    Vector3 local_scale() const;
    // 親の Transform オブジェクトから見た相対的なスケールを設定
    void local_scale(const Vector3& value);
    // 親の Transform オブジェクトから見た相対的な位置を取得
    Vector3 local_position() const;
    // 親の Transform オブジェクトから見た相対的な位置を設定
    void local_position(const Vector3& value);
    // 親の Transform オブジェクトから見た相対的な回転を取得
    Quaternion local_rotation() const;
    // 親の Transform オブジェクトから見た相対的な回転を設定
    void local_rotation(const Quaternion& value);
    // 親の Transform オブジェクトから見た相対的なオイラー角としての回転値を取得
    Vector3 local_euler_angles() const;
    // 親の Transform オブジェクトから見た相対的なオイラー角としての回転値を設定
    void local_euler_angles(const Vector3& value);
    // すべての子オブジェクトを親オブジェクトから切り離します
    void detach_children();
    // 親の Transform から切り離す
    void detach_parent();

private:
    // ワールド座標系の更新
    void update_world_transform(const Transform* parent);

private:
    // ポジション (ワールド座標系)
    Vector3 position_{ 0.0f, 0.0f, 0.0f };
    // 回転 (ワールド座標系)
    Quaternion rotation_{ 0.0f, 0.0f, 0.0f, 1.0f };
    // スケール (ワールド座標系)
    Vector3 scale_{ 1.0f, 1.0f, 1.0f };

    // ポジション (ローカル座標系)
    Vector3 local_position_{ 0.0f, 0.0f, 0.0f };
    // 回転 (ローカル座標系)
    Quaternion local_rotation_{ 0.0f, 0.0f, 0.0f, 1.0f };
    // スケール (ローカル座標系)
    Vector3 local_scale_{ 1.0f, 1.0f, 1.0f };

    // 親のトランスフォーム
    Transform* parent_{ nullptr };
    // 子のトランスフォーム
    std::list<Transform*> children_;
};

#endif