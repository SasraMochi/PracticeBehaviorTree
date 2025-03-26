#include "Player.h"

#include "Math/Screen.h"
#include "DxLib.h"

Player::Player()
{
	position_ = { Screen::Width / 2, Screen::Height / 2 };
}

Player::~Player()
{
}

void Player::update(float delta_time)
{
	Vector2 velocity{ 0.f, 0.f };

	// CheckHitKey�𐔒l�����Ĉړ��������v�Z
	// true��1�Afalse��0�Ƃ��ĕԂ����
	velocity.y = CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W);
	velocity.x = CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A);

	// ���͂�����Ă���Ƃ��̂݌v�Z
	if (velocity.magnitude() > 0.f) {
		position_ += velocity.normalized() * mSpeed;
	}
}

void Player::draw() const
{
	DrawCircle(position_.x, position_.y, 32, GetColor(0, 255, 0), TRUE);
}

void Player::draw_transparent() const
{
}

void Player::draw_gui() const
{
}
