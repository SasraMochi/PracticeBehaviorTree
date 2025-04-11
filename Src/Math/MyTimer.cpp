#include "MyTimer.h"

MyTimer::MyTimer()
	: mMaxTime(0)
	, mNowTime(0)
{
}

MyTimer::MyTimer(const float max_time)
	: mMaxTime(max_time)
	, mNowTime(max_time)
{
}

MyTimer::~MyTimer()
{
}

void MyTimer::reset()
{
	mNowTime = mMaxTime;
}

void MyTimer::reset(const float max_time)
{
	set_max_time(max_time);
	reset();
}

void MyTimer::set_max_time(const float max_time)
{
	mMaxTime = max_time;
}

void MyTimer::update(const float delta_time)
{
	if (is_end()) return;

	mNowTime -= delta_time;
}

bool MyTimer::is_end() const
{
	return mNowTime <= 0.f;
}
