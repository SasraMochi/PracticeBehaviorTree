#include "Attacker.h"

#include "Math/BehaviourTree/Inverter.h"
#include "Math/BehaviourTree/DebugDrawLeaf.h"
#include "Math/BehaviourTree/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/DebugFailLeaf.h"

Attacker::Attacker()
{
	mpBehaviourTree = new Selector();

#if 0
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
}

void Attacker::draw_transparent() const
{
}

void Attacker::draw_gui() const
{
}
