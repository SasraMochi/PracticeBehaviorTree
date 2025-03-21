#include "Transform.h"

// �f�X�g���N�^
Transform::~Transform() {
	// �q�I�u�W�F�N�g��؂藣��
	detach_children();
	// �e�I�u�W�F�g����؂藣��
	detach_parent();
}

// ���[���h��Ԃ� Transform�̐����擾
Vector3 Transform::forward() const {
	return rotation_ * Vector3::forward();
}

// ���[���h��Ԃ� Transform�̐���ݒ�
void Transform::forward(const Vector3& value) {
	rotation(Quaternion::look_rotation(value));
}

// ���[���h��Ԃ� Transform �̐Ԏ����擾
Vector3 Transform::right() const {
	return rotation_ * Vector3::right();
}

// ���[���h��Ԃ� Transform �̐Ԏ���ݒ�
void Transform::right(const Vector3& value) {
	rotation(Quaternion::from_to_rotation(Vector3::right(), value));
}

// ���[���h��Ԃ� Transform �̗Ύ����擾
Vector3 Transform::up() const {
	return rotation_ * Vector3::up();
}

// ���[���h��Ԃ� Transform �̗Ύ���ݒ�
void Transform::up(const Vector3& value) {
	rotation(Quaternion::from_to_rotation(Vector3::up(), value));
}

// �I�u�W�F�N�g�̃O���[�o���X�P�[�����擾
Vector3 Transform::lossy_scale() const {
	return scale_;
}

// ���[���h��Ԃ� Transform �̈ʒu���擾
Vector3 Transform::position() const {
	return position_;
}

// ���[���h��Ԃ� Transform �̈ʒu��ݒ�
void Transform::position(const Vector3& value) {
	if (parent_ != nullptr) {
		local_position(parent_->inverse_transform_point(value));
	}
	else {
		local_position(value);
	}
}

// Quaternion �Ƃ��ĕۑ�����郏�[���h��Ԃł� Transform �̉�]���擾
Quaternion Transform::rotation() const {
	return rotation_;
}

// Quaternion �Ƃ��ĕۑ�����郏�[���h��Ԃł� Transform �̉�]��ݒ�
void Transform::rotation(const Quaternion& value) {
	if (parent_ != nullptr) {
		local_rotation(Quaternion::inverse(parent_->rotation()) * value);
	}
	else {
		local_rotation(value);
	}
}

// �I�C���[�p�Ƃ��Ă̊p�x���擾
Vector3 Transform::euler_angles() const {
	return rotation_.euler_angles();
}

// �I�C���[�p�Ƃ��Ă̊p�x��ݒ�
void Transform::euler_angles(const Vector3& value) {
	rotation(Quaternion::euler(value));
}

// �Ώۂ� Transform ��ݒ肵�A���̕����ւƌ������܂�
void Transform::look_at(const Transform& target, const Vector3& world_up) {
	look_at(target.position(), world_up);
}

// �Ώۂ� Transform ��ݒ肵�A���̕����ւƌ������܂�
void Transform::look_at(const Vector3& target, const Vector3& world_up) {
	rotation(Quaternion::look_rotation(target - position_, world_up));
}

// Z ����eulers.z �x��]�AX���� euler.x �x��]�AY����eulers.y �x��]���܂�(���Ԃ͐���������)
void Transform::rotate(const Vector3& eulers, Space relative_to) {
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * Quaternion::euler(eulers.x, eulers.y, eulers.z));
	}
	else {
		rotation(Quaternion::euler(eulers.x, eulers.y, eulers.z) * rotation_);
	}
}

// axis ���̎���� angle �x�A��]���܂�
void Transform::rotate(const Vector3& axis, float angle, Space relative_to) {
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * Quaternion::angle_axis(angle, axis));
	}
	else {
		rotation(Quaternion::angle_axis(angle, axis) * rotation_);
	}
}

// ���[���h���W�� point �𒆐S�Ƃ�����(axis)�� angle �x��]�����܂�
void Transform::rotate_around(const Vector3& point, const Vector3& axis, float angle) {
	Quaternion q = Quaternion::angle_axis(angle, axis);
	position(point + q * (position_ - point));
	rotation(q * rotation_);
}

// translation �̕����Ƌ����Ɉړ����܂�
void Transform::translate(const Vector3& translation, Space relative_to) {
	if (relative_to == Space::Self) {
		position(position_ + transform_direction(translation));
	}
	else {
		position(position_ + translation);
	}
}

// ���[�J�����W���烏�[���h���W�֕ϊ������s��
Matrix4x4 Transform::local_to_world_matrix() const {
	return Matrix4x4::TRS(position_, rotation_, scale_);
}

// ���[���h���W���烍�[�J�����W�֕ϊ������s��
Matrix4x4 Transform::world_to_local_matrix() const {
	return local_to_world_matrix().inverse();
}

// ���[�J����Ԃ��烏�[���h��Ԃ� position ��ϊ����܂� (�X�P�[���E��]�E���s�ړ��j
Vector3 Transform::transform_point(const Vector3& position) const {
	return rotation_ * Vector3::scale(position, scale_) + position_;
}

// ���[�J����Ԃ��烏�[���h��Ԃ� vector ��ϊ����܂� (�X�P�[���E��]�j
Vector3 Transform::transform_vector(const Vector3& vector) const {
	return rotation_ * Vector3::scale(vector, scale_);
}

// ���[�J����Ԃ��烏�[���h��Ԃ� direction ��ϊ����܂�(��]�j
Vector3 Transform::transform_direction(const Vector3& direction) const {
	return rotation_ * direction;
}

// ���[���h��Ԃ��烍�[�J����Ԃ� position ��ϊ����܂�
Vector3 Transform::inverse_transform_point(const Vector3& position) const {
	Vector3 result = position;
	result -= position_;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;
}

// ���[���h��Ԃ��烍�[�J����Ԃ� vector ��ϊ����܂�
Vector3 Transform::inverse_transform_vector(const Vector3& vector) const {
	Vector3 result = vector;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;
}

// ���[���h��Ԃ��烍�[�J����Ԃ� direction ��ϊ����܂�
Vector3 Transform::inverse_transform_direction(const Vector3& direction) const {
	return Quaternion::inverse(rotation_) * direction;
}

// �e�� Transform ���擾
Transform* Transform::parent() const {
	return parent_;
}

// �e�� Transform ��ݒ�
void Transform::parent(Transform* parent) {
	set_parent(parent, true);
}

// �e�� Transform ��ݒ�
void Transform::set_parent(Transform* parent, bool world_position_stays) {
	// ���݂̐e����؂藣��
	detach_parent();
	// �V�����e��ݒ�
	parent_ = parent;
	if (parent_ != nullptr) {
		// ���݂̃��[���h��Ԃ�ۂ��H
		if (world_position_stays) {
			// ���[�J����Ԃ����X�V����
			local_rotation_ = Quaternion::inverse(parent_->rotation()) * rotation_;
			local_rotation_ = Quaternion::normalize(local_rotation_);
			local_position_ = parent_->inverse_transform_point(position_);
		}
		else {
			// ���݂̃��[�J����Ԃ��X�V�����Ƀ��[���h��Ԃ��X�V
			update_world_transform(parent_);
		}
		// �������g��e�̎q�ɓo�^
		parent_->children_.push_back(this);
	}
	else {
		// �e�����Ȃ���΁A���[�J����Ԃ̓��[���h��ԂƓ���
		local_rotation_ = rotation_;
		local_position_ = position_;
		local_scale_ = scale_;
	}
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃX�P�[�����擾
Vector3 Transform::local_scale() const {
	return local_scale_;
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃX�P�[����ݒ�
void Transform::local_scale(const Vector3& value) {
	local_scale_ = value;
	// ���[���h��Ԃ��X�V
	update_world_transform(parent_);
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�Ȉʒu���擾
Vector3 Transform::local_position() const {
	return local_position_;
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�Ȉʒu��ݒ�
void Transform::local_position(const Vector3& value) {
	local_position_ = value;
	// ���[���h��Ԃ��X�V
	update_world_transform(parent_);
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȉ�]���擾
Quaternion Transform::local_rotation() const {
	return local_rotation_;
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȉ�]��ݒ�
void Transform::local_rotation(const Quaternion& value) {
	local_rotation_ = value;
	local_rotation_ = Quaternion::normalize(local_rotation_);
	// ���[���h��Ԃ��X�V
	update_world_transform(parent_);
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃI�C���[�p�Ƃ��Ẳ�]�l���擾
Vector3 Transform::local_euler_angles() const {
	return local_rotation_.euler_angles();
}

// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃI�C���[�p�Ƃ��Ẳ�]�l��ݒ�
void Transform::local_euler_angles(const Vector3& value) {
	local_rotation(Quaternion::euler(value));
}

// ���ׂĂ̎q�I�u�W�F�N�g��e�I�u�W�F�N�g����؂藣���܂�
void Transform::detach_children() {
	// ���g�̐e���q�̐e�ɕύX����
	auto i = children_.begin();
	while (i != children_.end()) {
		// ���̗v�f�̃C�e���[�^���擾���Ă���
		auto j = std::next(i);
		// ���݂̐e��V�����e�Ƃ���
		(*i)->parent(parent_);
		// ���ɐi�߂�
		i = j;
	}
}

// �e�� Transform ����؂藣��
void Transform::detach_parent() {
	if (parent_ != nullptr) {
		// �e�̃��X�g���玩�g���폜
		parent_->children_.remove(this);
		parent_ = nullptr;
	}
}

// ���[���h��Ԃ̍X�V
void Transform::update_world_transform(const Transform* parent) {
	if (parent != nullptr) {
		// ���[���h��Ԃ̍X�V
		position_ = parent->transform_point(local_position_);
		rotation_ = parent->rotation_ * local_rotation_;
		rotation_ = Quaternion::normalize(rotation_);
		scale_ = Vector3::scale(parent->scale_, local_scale_);
	}
	else {
		// �e�����Ȃ���΃��[�J����Ԃƃ��[���h��Ԃ͓���
		position_ = local_position_;
		rotation_ = local_rotation_;
		scale_ = local_scale_;
	}
	// �q���̃��[���h��Ԃ��X�V
	for (auto child : children_) {
		child->update_world_transform(this);
	}
}