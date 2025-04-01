#include "Player.h"

#include "Math/Screen.h"
#include "DxLib.h"

Player::Player()
{
	// �����ʒu�̐ݒ�
	mPosition = { Screen::Width / 2, Screen::Height / 2 };
	mTag = "PlayerTag";
	mName = "Player";

	Vector2 min = mPosition - Vector2{ -30.f, -30.f };
	Vector2 max = mPosition - Vector2{ 30.f, 30.f };
	mCollider = MyRectangle{ min, max };
}

Player::~Player()
{
}

void Player::update(float delta_time)
{
	mVelocity = Vector2::zero();
	Vector2 velocity = Vector2::zero();

	// CheckHitKey�𐔒l�����Ĉړ��������v�Z
	// true��1�Afalse��0�Ƃ��ĕԂ����
	velocity.y = CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W);
	velocity.x = CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A);

	// ���͂�����Ă���Ƃ��̂݌v�Z
	if (velocity.magnitude() > 0.f) {
		mVelocity = velocity.normalized() * mSpeed;

		mPosition += mVelocity * delta_time;
	}

	mCollider = mCollider.translate(mVelocity * delta_time);
}

void Player::draw() const
{
	DrawCircle(mPosition.x, mPosition.y, 32, GetColor(0, 255, 0), TRUE);
}

void Player::draw_transparent() const
{
}

void Player::draw_gui() const
{
	mCollider.draw_debug();
}
