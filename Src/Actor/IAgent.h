#pragma once

class Vector2;

class IAgent {
public:
	virtual ~IAgent() = default;

	virtual const Vector2& get_position() const = 0;
	virtual void move_towards(const Vector2& target, float speed) = 0;

	virtual const float get_health() const = 0;
	virtual void attack() = 0;
};