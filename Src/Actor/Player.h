#pragma once

#include "Actor.h"
#include "Math/Vector2.h"

#include "Actor/Actor.h"

class Player : public Actor{
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
	// ダメージ
	void damage(const int damage_value);

private:
	float mSpeed = 4.f;
	float mHealth = 100.f;
};