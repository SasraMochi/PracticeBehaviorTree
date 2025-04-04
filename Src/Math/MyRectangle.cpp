#include "MyRectangle.h"

MyRectangle::MyRectangle()
	: mMin(Vector2::zero())
	, mMax(Vector2::zero())
{
}

MyRectangle::MyRectangle(float left, float top, float right, float bottom)
	: mMin(left, top)
	, mMax(right, bottom)
{
}

MyRectangle::MyRectangle(const Vector2& min, const Vector2& max)
	: mMin(min)
	, mMax(max)
{
}

bool MyRectangle::contains(const Vector2& position) const
{
	return (mMin.x <= position.x && position.x <= mMax.x)
		&& (mMin.y <= position.y && position.y <= mMax.y);
}

bool MyRectangle::intersects(const MyRectangle& other) const
{
	if (mMin.x > other.mMax.x) return false;
	if (mMax.x < other.mMin.x) return false;
	if (mMin.y > other.mMax.y) return false;
	if (mMax.y < other.mMin.y) return false;

	return true;
}

MyRectangle MyRectangle::translate(const Vector2& position) const
{
	return MyRectangle(mMin + position, mMax + position);
}

MyRectangle MyRectangle::expand(const Vector2& size) const
{
	return MyRectangle(mMin - size, mMax + size);
}

float MyRectangle::width() const
{
	return mMax.x - mMin.x;
}

float MyRectangle::height() const
{
	return mMax.y - mMin.y;
}

const Vector2& MyRectangle::get_min() const
{
	return mMin;
}

const Vector2& MyRectangle::get_max() const
{
	return mMax;
}

void MyRectangle::draw_debug(int is_fill, unsigned int color) const
{
	DrawBox(mMin.x, mMin.y, mMax.x, mMax.y, color, is_fill);
}
