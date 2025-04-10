#include "Attacker.h"

#include "DxLib.h"
#include "World/IWorld.h"

#include "Actor/BlackBoard.h"
#include "Actor/AttackCollider.h"
#include "Math/BehaviourTree/BehaviourTreeBulider.h"

#include "Math/BehaviourTree/Decorator/Inverter.h"
#include "Math/BehaviourTree/Leaf/DebugDrawLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugFailLeaf.h"

Attacker::Attacker(IWorld* world)
	:mHealthBar{ this }
{
	mpWorld = world;
	mTag = "EnemyTag";
	mName = "Attacker";
	mAttackPower = 1;

	mpBlackBoard = new BlackBoard();
	mpBlackBoard->set_value<IAgent*>("Agent", this);
	mpBlackBoard->set_value<Vector2>("PlayerPos", Vector2::zero());

	mpBehaviourTree = BehaviourTreeBuilder::BuildAttackerTree(mpBlackBoard);

	Vector2 min = mPosition - Vector2{ 30.f, 30.f };
	Vector2 max = mPosition + Vector2{ 30.f, 30.f };
	mCollider = MyRectangle{ min, max };
}

Attacker::~Attacker()
{
	delete(mpBehaviourTree);
}

void Attacker::update(float delta_time)
{
	Vector2 pos = mpWorld->find_actor("Player")->position();
	mpBlackBoard->set_value<Vector2>("PlayerPos", pos);

	mpBehaviourTree->tick();

	mPosition += mVelocity * delta_time;
	mCollider = mCollider.translate(mVelocity * delta_time);

	mVelocity = Vector2::zero();
}

void Attacker::draw() const
{
	DrawCircle(mPosition.x, mPosition.y, 32, GetColor(255, 0, 0), TRUE);
}

void Attacker::draw_transparent() const
{
}

void Attacker::draw_gui() const
{
	mCollider.draw_debug();
}

const Vector2& Attacker::get_position() const
{
	return mPosition;
}

void Attacker::move_towards(const Vector2& target, float speed)
{
	mVelocity = target * speed;
}

const float Attacker::get_health() const
{
	return mHealth.GetHealth();
}

void Attacker::attack()
{
	Vector2 min, max;

	min = mPosition - Vector2{ 75.f, 75.f };
	max = mPosition + Vector2{ 75.f, 75.f };
	MyRectangle attack_collider{ min, max };

	mpWorld->add_actor(new AttackCollider{ mpWorld,attack_collider, mTag, 15.f , 10.f });
}
