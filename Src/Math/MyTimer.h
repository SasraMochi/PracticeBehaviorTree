#pragma once

class MyTimer {
public:
	MyTimer(float max_time);

	~MyTimer();

	void reset();

	void set_max_time(float max_time);

	void update(float delta_time);

	bool is_end() const;

private:
	float mMaxTime = 100;
	float mNowTime = 100;
};