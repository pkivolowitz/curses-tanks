#pragma once
#include "ground.hpp"

enum Side
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
	void Draw(Ground & ground);
	void Initialize(int column, Side side);
	void DrawSettings(int turn);
	void PowerUp();
	void PowerDown();
	void AngleUp();
	void AngleDown();
	void Health();
	bool Hit(int l, int c, Player &players, Ground &g);

	int col;
	double power;
	double angle;
	Side s;
	int health;

	static const int power_increment;
	static const double angle_increment;
	static const int health_increment;
};
