#pragma once

#include "Actor/Actor.h"
#include "UI/BarGauge.h"
#include "Math/MyTimer.h"
#include "Actor/ActorHealth.h"

class Player : public Actor{
const float cCoolTime = 60.f;

public:
	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

	// 更新
	virtual void update(float delta_time);

	// 描画
	virtual void draw() const;

	//半透明の描画
	virtual void draw_transparent() const;

	//GUIの描画
	virtual void draw_gui() const;

	// 衝突リアクション
	virtual void react(Actor& other) override;

private:
	float mSpeed = 4.f;

	BarGauge mHealthBar;
};