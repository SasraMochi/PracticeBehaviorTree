#pragma once

class ActorHealth {
public:
	ActorHealth(const float max_health);

	~ActorHealth();

	void SetHealth(const float health);

	void Damage(const float decrease_amount);

	const float GetHealth() const;

	bool GetIsDead() const;

private:
	float mHealth;
	float mMaxHealth;
};
