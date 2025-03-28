#pragma once

#include "Actor/Actor.h"
#include "Actor/IAgent.h"
#include "Math/BehaviourTree/Composite/Selector.h"

#include "Math/Vector2.h"

class IWorld;

class Attacker : public Actor, public IAgent {
public:
	//コンストラクタ
	Attacker(IWorld* world);
	//デストラクタ
	~Attacker();
	//更新
	void update(float delta_time);
	//描画
	void draw() const;
	//半透明の描画
	void draw_transparent() const;
	//GUIの描画
	void draw_gui() const;

public:
	const Vector2& get_position() const override;
	void move_towards(const Vector2& target, float speed) override;

private:
	INode* mpBehaviourTree = nullptr;
};
