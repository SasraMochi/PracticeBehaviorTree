#pragma once

#include "Actor/Actor.h"
#include "Math/BehaviourTree/Selector.h"

class Attacker : public Actor {
public:
	//コンストラクタ
	Attacker();
	//デストラクタ
	~Attacker();
	//更新
	virtual void update(float delta_time);
	//描画
	virtual void draw() const;
	//半透明の描画
	virtual void draw_transparent() const;
	//GUIの描画
	virtual void draw_gui() const;

private:
	Selector* mpBehaviourTree = nullptr;
};
