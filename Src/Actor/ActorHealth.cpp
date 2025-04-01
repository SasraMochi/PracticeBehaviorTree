#include "ActorHealth.h"

#include <algorithm>

constexpr float cMinHealth = 0;

ActorHealth::ActorHealth(const float max_health)
	: mHealth(max_health)
	, mMaxHealth(max_health)
{
}

ActorHealth::~ActorHealth()
{
}

void ActorHealth::SetHealth(const float health)
{
	mHealth = health;
}

void ActorHealth::Damage(const float decrease_amount)
{
	mHealth = std::clamp(mHealth - decrease_amount, cMinHealth, mMaxHealth);
}

const float ActorHealth::GetHealth() const
{
	return mHealth;
}

bool ActorHealth::GetIsDead() const
{
	if (mHealth == 0) return true;

	return false;
}
