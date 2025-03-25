#include "Player.h"

#include "Math/Screen.h"
#include "DxLib.h"

Player::Player()
{
	mPosition = { Screen::Width / 2, Screen::Height / 2 };
}

Player::~Player()
{
}

void Player::update(float delta_time)
{
	Vector2 velocity;
	if (CheckHitKey(KEY_INPUT_W)) {
		velocity.y = -1.f;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		velocity.y = 1.f;
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		velocity.x = -1.f;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		velocity.x = 1.f;
	}

	mPosition += velocity.normalized() * mSpeed;
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
}
