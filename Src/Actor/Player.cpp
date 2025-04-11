#include "Player.h"

#include "Math/Screen.h"
#include "DxLib.h"

#include <algorithm>

Player::Player()
	: mHealthBar{ this , mHealth.GetHealth() }
{
	// 初期位置の設定
	mPosition = { Screen::Width / 2, Screen::Height / 2 };
	mTag = "PlayerTag";
	mName = "Player";
	mAttackPower = 10;

	Vector2 min = mPosition - Vector2{ 30.f, 30.f };
	Vector2 max = mPosition + Vector2{ 30.f, 30.f };
	mCollider = MyRectangle{ min, max };

	mCoolTimer.reset(cCoolTime);
}

Player::~Player()
{
}

void Player::update(float delta_time)
{
	if (!mIsEnableCollider) {
		mCoolTimer.update(delta_time);

		if (mCoolTimer.is_end()) {
			mIsEnableCollider = true;
		}
	}

	mVelocity = Vector2::zero();
	Vector2 velocity = Vector2::zero();

	// CheckHitKeyを数値化して移動方向を計算
	// trueは1、falseは0として返される
	velocity.y = static_cast<float>(CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W));
	velocity.x = static_cast<float>(CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A));

	// 入力がされているときのみ計算
	if (velocity.magnitude() > 0.f) {
		mVelocity = velocity.normalized() * mSpeed;

		mPosition += mVelocity * delta_time;
	}

	mCollider = mCollider.translate(mVelocity * delta_time);

	mHealthBar.update(delta_time, mHealth.GetHealth());
}

void Player::draw() const
{
	DrawCircle(mPosition.int_x(), mPosition.int_y(), 32, GetColor(0, 255, 0), TRUE);

	mHealthBar.draw();
}

void Player::draw_transparent() const
{
}

void Player::draw_gui() const
{
	mCollider.draw_debug();
}

void Player::react(Actor& other)
{
	if (other.tag() == "EnemyTag") {
		damage(other.attack_power());
	}
}
