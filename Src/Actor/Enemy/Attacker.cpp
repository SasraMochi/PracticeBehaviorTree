#include "Attacker.h"

#include "DxLib.h"

#include "Math/BehaviourTree/Inverter.h"
#include "Math/BehaviourTree/Leaf/DebugDrawLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugFailLeaf.h"

Attacker::Attacker()
{
	tag_ = "EnemyTag";
	name_ = "Attacker";

	mpBehaviourTree = new Selector();

#if 1
	mpBehaviourTree->AddNode(new Inverter(new DebugDrawLeaf(1)));
	mpBehaviourTree->AddNode(new Inverter(new DebugDrawLeaf(2)));
	mpBehaviourTree->AddNode(new DebugDrawLeaf(3));
#endif
}

Attacker::~Attacker()
{
	delete(mpBehaviourTree);
}

void Attacker::update(float delta_time)
{
	mpBehaviourTree->Run();
}

void Attacker::draw() const
{
	DrawCircle(position_.x, position_.y, 32, GetColor(255, 0, 0), TRUE);
}

void Attacker::draw_transparent() const
{
}

void Attacker::draw_gui() const
{
}
