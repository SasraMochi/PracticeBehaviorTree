#pragma once

class Actor;

class BarGauge {
public:
	BarGauge(Actor* owner, const float max_value = 100);

	~BarGauge();

	void setMaxValue(const int max_value);

	void update(const float delta_time, const int value);

	void draw() const;

private:
	Actor* mpOwner{ nullptr };

	int mMaxValue = 100;
	int mValue = 50;
};