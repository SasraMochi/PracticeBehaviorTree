#pragma once

#include "Actor.h"
#include "Math/Vector2.h"

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

private:
	float mSpeed = 4.f;
	float mHealth = 100.f;
};