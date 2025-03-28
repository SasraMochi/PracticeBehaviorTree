#include "Player.h"

#include "Math/Screen.h"
#include "DxLib.h"

Player::Player()
{
	// 初期位置の設定
	mPosition = { Screen::Width / 2, Screen::Height / 2 };
	mTag = "PlayerTag";
	mName = "Player";
}

Player::~Player()
{
}

void Player::update(float delta_time)
{
	Vector2 velocity{ 0.f, 0.f };

	// CheckHitKeyを数値化して移動方向を計算
	// trueは1、falseは0として返される
	velocity.y = CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W);
	velocity.x = CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A);

	// 入力がされているときのみ計算
	if (velocity.magnitude() > 0.f) {
		mPosition += velocity.normalized() * mSpeed;
	}
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
