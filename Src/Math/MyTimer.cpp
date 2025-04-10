#include "MyTimer.h"

MyTimer::MyTimer(float max_time)
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

void MyTimer::set_max_time(float max_time)
{
	mMaxTime = max_time;
}

void MyTimer::update(float delta_time)
{
	if (is_end()) return;

	mNowTime -= delta_time;
}

bool MyTimer::is_end() const
{
	return mNowTime <= 0.f;
}
