#pragma once

#include "Actor/Actor.h"
#include "Actor/IAgent.h"
#include "Math/BehaviourTree/Selector.h"

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
	const Vector2& GetPosition() const override;
	void MoveTowards(const Vector2& target, float speed) override;

private:
	INode* mpBehaviourTree = nullptr;

	// Vector2 mPlayerPosition = { 0.f, 0.f };
};
