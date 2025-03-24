#include "Attacker.h"

#include "Math/BehaviourTree/DebugDrawLeaf.h"

Attacker::Attacker()
{
	mpBehaviourTree = new Selector();
	mpBehaviourTree->AddNode(new DebugDrawLeaf("1"));
	mpBehaviourTree->AddNode(new DebugDrawLeaf("2"));
	mpBehaviourTree->AddNode(new DebugDrawLeaf("3"));
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
