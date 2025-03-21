#include "Transform.h"

// デストラクタ
Transform::~Transform() {
	// 子オブジェクトを切り離す
	detach_children();
	// 親オブジェトから切り離す
	detach_parent();
}

// ワールド空間の Transformの青軸を取得
Vector3 Transform::forward() const {
	return rotation_ * Vector3::forward();
}

// ワールド空間の Transformの青軸を設定
void Transform::forward(const Vector3& value) {
	rotation(Quaternion::look_rotation(value));
}

// ワールド空間の Transform の赤軸を取得
Vector3 Transform::right() const {
	return rotation_ * Vector3::right();
}

// ワールド空間の Transform の赤軸を設定
void Transform::right(const Vector3& value) {
	rotation(Quaternion::from_to_rotation(Vector3::right(), value));
}

// ワールド空間の Transform の緑軸を取得
Vector3 Transform::up() const {
	return rotation_ * Vector3::up();
}

// ワールド空間の Transform の緑軸を設定
void Transform::up(const Vector3& value) {
	rotation(Quaternion::from_to_rotation(Vector3::up(), value));
}

// オブジェクトのグローバルスケールを取得
Vector3 Transform::lossy_scale() const {
	return scale_;
}

// ワールド空間の Transform の位置を取得
Vector3 Transform::position() const {
	return position_;
}

// ワールド空間の Transform の位置を設定
void Transform::position(const Vector3& value) {
	if (parent_ != nullptr) {
		local_position(parent_->inverse_transform_point(value));
	}
	else {
		local_position(value);
	}
}

// Quaternion として保存されるワールド空間での Transform の回転を取得
Quaternion Transform::rotation() const {
	return rotation_;
}

// Quaternion として保存されるワールド空間での Transform の回転を設定
void Transform::rotation(const Quaternion& value) {
	if (parent_ != nullptr) {
		local_rotation(Quaternion::inverse(parent_->rotation()) * value);
	}
	else {
		local_rotation(value);
	}
}

// オイラー角としての角度を取得
Vector3 Transform::euler_angles() const {
	return rotation_.euler_angles();
}

// オイラー角としての角度を設定
void Transform::euler_angles(const Vector3& value) {
	rotation(Quaternion::euler(value));
}

// 対象の Transform を設定し、その方向へと向かせます
void Transform::look_at(const Transform& target, const Vector3& world_up) {
	look_at(target.position(), world_up);
}

// 対象の Transform を設定し、その方向へと向かせます
void Transform::look_at(const Vector3& target, const Vector3& world_up) {
	rotation(Quaternion::look_rotation(target - position_, world_up));
}

// Z 軸でeulers.z 度回転、X軸で euler.x 度回転、Y軸でeulers.y 度回転します(順番は説明した順)
void Transform::rotate(const Vector3& eulers, Space relative_to) {
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * Quaternion::euler(eulers.x, eulers.y, eulers.z));
	}
	else {
		rotation(Quaternion::euler(eulers.x, eulers.y, eulers.z) * rotation_);
	}
}

// axis 軸の周りに angle 度、回転します
void Transform::rotate(const Vector3& axis, float angle, Space relative_to) {
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * Quaternion::angle_axis(angle, axis));
	}
	else {
		rotation(Quaternion::angle_axis(angle, axis) * rotation_);
	}
}

// ワールド座標の point を中心とした軸(axis)で angle 度回転させます
void Transform::rotate_around(const Vector3& point, const Vector3& axis, float angle) {
	Quaternion q = Quaternion::angle_axis(angle, axis);
	position(point + q * (position_ - point));
	rotation(q * rotation_);
}

// translation の方向と距離に移動します
void Transform::translate(const Vector3& translation, Space relative_to) {
	if (relative_to == Space::Self) {
		position(position_ + transform_direction(translation));
	}
	else {
		position(position_ + translation);
	}
}

// ローカル座標からワールド座標へ変換した行列
Matrix4x4 Transform::local_to_world_matrix() const {
	return Matrix4x4::TRS(position_, rotation_, scale_);
}

// ワールド座標からローカル座標へ変換した行列
Matrix4x4 Transform::world_to_local_matrix() const {
	return local_to_world_matrix().inverse();
}

// ローカル空間からワールド空間へ position を変換します (スケール・回転・平行移動）
Vector3 Transform::transform_point(const Vector3& position) const {
	return rotation_ * Vector3::scale(position, scale_) + position_;
}

// ローカル空間からワールド空間へ vector を変換します (スケール・回転）
Vector3 Transform::transform_vector(const Vector3& vector) const {
	return rotation_ * Vector3::scale(vector, scale_);
}

// ローカル空間からワールド空間へ direction を変換します(回転）
Vector3 Transform::transform_direction(const Vector3& direction) const {
	return rotation_ * direction;
}

// ワールド空間からローカル空間へ position を変換します
Vector3 Transform::inverse_transform_point(const Vector3& position) const {
	Vector3 result = position;
	result -= position_;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;
}

// ワールド空間からローカル空間へ vector を変換します
Vector3 Transform::inverse_transform_vector(const Vector3& vector) const {
	Vector3 result = vector;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;
}

// ワールド空間からローカル空間へ direction を変換します
Vector3 Transform::inverse_transform_direction(const Vector3& direction) const {
	return Quaternion::inverse(rotation_) * direction;
}

// 親の Transform を取得
Transform* Transform::parent() const {
	return parent_;
}

// 親の Transform を設定
void Transform::parent(Transform* parent) {
	set_parent(parent, true);
}

// 親の Transform を設定
void Transform::set_parent(Transform* parent, bool world_position_stays) {
	// 現在の親から切り離す
	detach_parent();
	// 新しい親を設定
	parent_ = parent;
	if (parent_ != nullptr) {
		// 現在のワールド空間を保つか？
		if (world_position_stays) {
			// ローカル空間だけ更新する
			local_rotation_ = Quaternion::inverse(parent_->rotation()) * rotation_;
			local_rotation_ = Quaternion::normalize(local_rotation_);
			local_position_ = parent_->inverse_transform_point(position_);
		}
		else {
			// 現在のローカル空間を更新せずにワールド空間を更新
			update_world_transform(parent_);
		}
		// 自分自身を親の子に登録
		parent_->children_.push_back(this);
	}
	else {
		// 親がいなければ、ローカル空間はワールド空間と同じ
		local_rotation_ = rotation_;
		local_position_ = position_;
		local_scale_ = scale_;
	}
}

// 親の Transform オブジェクトから見た相対的なスケールを取得
Vector3 Transform::local_scale() const {
	return local_scale_;
}

// 親の Transform オブジェクトから見た相対的なスケールを設定
void Transform::local_scale(const Vector3& value) {
	local_scale_ = value;
	// ワールド空間を更新
	update_world_transform(parent_);
}

// 親の Transform オブジェクトから見た相対的な位置を取得
Vector3 Transform::local_position() const {
	return local_position_;
}

// 親の Transform オブジェクトから見た相対的な位置を設定
void Transform::local_position(const Vector3& value) {
	local_position_ = value;
	// ワールド空間を更新
	update_world_transform(parent_);
}

// 親の Transform オブジェクトから見た相対的な回転を取得
Quaternion Transform::local_rotation() const {
	return local_rotation_;
}

// 親の Transform オブジェクトから見た相対的な回転を設定
void Transform::local_rotation(const Quaternion& value) {
	local_rotation_ = value;
	local_rotation_ = Quaternion::normalize(local_rotation_);
	// ワールド空間を更新
	update_world_transform(parent_);
}

// 親の Transform オブジェクトから見た相対的なオイラー角としての回転値を取得
Vector3 Transform::local_euler_angles() const {
	return local_rotation_.euler_angles();
}

// 親の Transform オブジェクトから見た相対的なオイラー角としての回転値を設定
void Transform::local_euler_angles(const Vector3& value) {
	local_rotation(Quaternion::euler(value));
}

// すべての子オブジェクトを親オブジェクトから切り離します
void Transform::detach_children() {
	// 自身の親を子の親に変更する
	auto i = children_.begin();
	while (i != children_.end()) {
		// 次の要素のイテレータを取得しておく
		auto j = std::next(i);
		// 現在の親を新しい親とする
		(*i)->parent(parent_);
		// 次に進める
		i = j;
	}
}

// 親の Transform から切り離す
void Transform::detach_parent() {
	if (parent_ != nullptr) {
		// 親のリストから自身を削除
		parent_->children_.remove(this);
		parent_ = nullptr;
	}
}

// ワールド空間の更新
void Transform::update_world_transform(const Transform* parent) {
	if (parent != nullptr) {
		// ワールド空間の更新
		position_ = parent->transform_point(local_position_);
		rotation_ = parent->rotation_ * local_rotation_;
		rotation_ = Quaternion::normalize(rotation_);
		scale_ = Vector3::scale(parent->scale_, local_scale_);
	}
	else {
		// 親がいなければローカル空間とワールド空間は同じ
		position_ = local_position_;
		rotation_ = local_rotation_;
		scale_ = local_scale_;
	}
	// 子供のワールド空間を更新
	for (auto child : children_) {
		child->update_world_transform(this);
	}
}