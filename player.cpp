#include <sstream>
#include <iomanip>
#include "player.hpp"

#if defined(WIN32)
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#endif

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const int Player::power_increment = 1;
const double Player::angle_increment = 1;
const int Player::health_increment = 1;
const int Player::wins_increment = 1;

Player::Player()
{
	s = LEFT;
	col = 0;
	angle = 45.0;
	power = 50.0;
	health = 3;
	wins = 0;
}

void Player::Initialize(int column, Side side)
{
	col = column;
	s = side;
}

void Player::Draw(Ground & g)
{
	mvaddch(g.ground.at(col) - 1, col + 1, '@');
}

void Player::PowerUp()
{
	power += power_increment;
}

void Player::PowerDown()
{
	power -= power_increment;
	if (power <= 0)
		power = power_increment;
}

void Player::AngleUp()
{
	angle += angle_increment;
	if (angle >= 90.0)
		angle = 90.0;
}

void Player::AngleDown()
{
	angle -= angle_increment;
	if (angle < 0.0)
		angle = 0.0;
}

void Player::Health()
{

	health -= health_increment;
}

void Player::Wins()
{
	wins += wins_increment;
}

void Player::DrawSettings(int turn)
{
	bool my_turn = (turn == 0 && s == LEFT) || (turn == 1 && s == RIGHT);

	int starting_column = 2;
	int line = 1;
	char player = (s == LEFT) ? '1' : '2';
	stringstream ss;

	if (s == RIGHT)
		starting_column = COLS - 18;

	if (my_turn)
		attron(A_STANDOUT);
	ss << setw(10) << left << "Player:" << player;
	mvaddstr(line++, starting_column, ss.str().c_str());
	if (my_turn)
		attroff(A_STANDOUT);

	ss = stringstream();
	ss << setw(10) << left << "Angle: " << setw(6) << angle;
	mvaddstr(line++, starting_column, ss.str().c_str());
	
	ss = stringstream();
	ss << setw(10) << left << "Power: " << setw(6) << power;
	mvaddstr(line++, starting_column, ss.str().c_str());

	ss = stringstream();
	ss << setw(10) << left << "Health: " << setw(6) << health;
	mvaddstr(line++, starting_column, ss.str().c_str());

	ss = stringstream();
	ss << setw(10) << left << "Wins: " << setw(6) << wins;
	mvaddstr(line++, starting_column, ss.str().c_str());
}


