#include "BarGauge.h"

#include "DxLib.h"
#include "Actor/Actor.h"
#include "Math/Vector2.h"

#include <cmath>
#include <algorithm>

BarGauge::BarGauge(Actor* owner, const float max_value)
{
	mpOwner = owner;
	setMaxValue(std::roundf(max_value));
}

BarGauge::~BarGauge()
{
}

void BarGauge::setMaxValue(const int max_value)
{
	mMaxValue = max_value;
}

void BarGauge::update(const float delta_time, const int value)
{
	mValue = value;
}

void BarGauge::draw() const
{
	Vector2 owner_pos = mpOwner->position();

	const int cBarWidth = 150;
	const int cBarHeight = 20;

	int left = owner_pos.x - cBarWidth / 2;
	int top = owner_pos.y - 70;
	int right = owner_pos.x + cBarWidth / 2;
	int bottom = top + cBarHeight;

	// 枠の背景(黒)
	DrawBox(left, top, right, bottom, GetColor(0, 0, 0), TRUE);

	// 枠（白）
	DrawBox(left, top, right, bottom, GetColor(255, 255, 255), FALSE);

	// HPの割合
	float ratio = static_cast<float>(mValue) / mMaxValue;
	ratio = std::clamp(ratio, 0.0f, 1.0f);  // 安全のため

	// 現在のHPバー（緑）
	int bar_right = left + static_cast<int>(cBarWidth * ratio);
	DrawBox(left, top, bar_right, bottom, GetColor(0, 255, 0), TRUE);
}
