#include "Vec2d.hpp"

using namespace std;

Vec2d::Vec2d(double x_comp, double y_comp)
{
	x = x_comp;
	y = y_comp;
}

Vec2d Vec2d::operator=(Vec2d & other)
{
	x = other.x;
	y = other.y;

	return Vec2d(other);
}

Vec2d Vec2d::operator*(double d)
{
	x *= d;
	y *= d;
	return Vec2d(*this);
}

Vec2d Vec2d::operator+(Vec2d & other)
{
	x += other.x;
	y += other.y;
	return Vec2d(*this);
}


