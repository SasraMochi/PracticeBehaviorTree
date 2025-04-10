#include "AttackCollider.h"
#include "Math/MyRectangle.h"

AttackCollider::AttackCollider(IWorld* world, MyRectangle& collider,
	const std::string& owner_tag,
	float lifespan,
	float attack_power)
	: mOwnerTag(owner_tag)
	, mLifeSpan(lifespan)
{
	mpWorld = world;
	mTag = owner_tag;
	mName = "AttackCollider";
	mpBlackBoard = nullptr;
	mPosition = Vector2{ 0.f, 0.f };

	mAttackPower = attack_power;

	mCollider = collider;
}

AttackCollider::~AttackCollider()
{
}

void AttackCollider::update(float delta_time)
{
	if (mLifeSpan <= 0.f) {
		die();
	}

	mLifeSpan -= delta_time;
}

void AttackCollider::draw() const
{

}

void AttackCollider::draw_gui() const
{
	mCollider.draw_debug(0, GetColor(255, 255, 0));
}

void AttackCollider::react(Actor& other)
{

}
