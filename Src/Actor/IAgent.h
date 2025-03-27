#pragma once

class Vector2;

class IAgent {
public:
	virtual ~IAgent() = default;

	virtual const Vector2& GetPosition() const = 0;
	virtual void MoveTowards(const Vector2& target, float speed) = 0;
};