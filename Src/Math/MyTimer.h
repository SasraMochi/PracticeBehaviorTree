#pragma once

class MyTimer {
public:
	MyTimer();
	MyTimer(const float max_time);

	~MyTimer();

	void reset();

	void reset(const float max_time);

	void set_max_time(const float max_time);

	void update(const float delta_time);

	bool is_end() const;

private:
	float mMaxTime = 0;
	float mNowTime = 0;
};