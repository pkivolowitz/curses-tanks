#pragma once
#include "player.hpp"

class Vec2d
{
public:
	Vec2d(double x_comp, double y_comp);
	Vec2d operator=(Vec2d &other);
	Vec2d operator*(double);
	Vec2d operator+(Vec2d &other);

	double x;
	double y;
};