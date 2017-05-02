//Lesya Protasova
//testing-math branch

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>
#include <Windows.h>

#include "curses.h"
#include "ground.hpp"
#include "player.hpp"

using namespace std;

extern int lines;
extern int cols;
extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

struct Coord2D
{
	double xComponent = 0.0;
	double yComponent = 0.0;
	void Initialize(double, double);

	//overloads
	Coord2D operator*(int);
	Coord2D operator*(double);
	Coord2D operator+(const Coord2D &);
};

void Coord2D::Initialize(double xVal, double yVal)
{
	xComponent = xVal;
	yComponent = yVal;
}

Coord2D Coord2D::operator* (int multiplier)
{
	Coord2D productCoord;
	productCoord.xComponent = this->xComponent * multiplier;
	productCoord.yComponent = this->yComponent * multiplier;
	//xComponent *= multiplier;
	//yComponent *= multiplier;
	return productCoord;
}

Coord2D Coord2D::operator* (double multiplier)
{
	Coord2D productCoord;
	productCoord.xComponent = this->xComponent * multiplier;
	productCoord.yComponent = this->yComponent * multiplier;
	return productCoord;
}

Coord2D Coord2D::operator+ (const Coord2D & otherCoord)
{
	Coord2D sumCoord;
	sumCoord.xComponent = this->xComponent + otherCoord.xComponent;
	sumCoord.yComponent = this->yComponent + otherCoord.yComponent;
	return sumCoord;
}

void DrawScreen(Ground & g, Player * players, int turn)
{
	erase();
	box(stdscr, 0, 0);
	g.Draw();
	players[0].Draw(g);
	players[1].Draw(g);
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}

//http://www.iforce2d.net/b2dtut/projected-trajectory

bool Shoot(Ground & g, Player * players, int turn)
{
	//conversion from degrees to radians
	double angle = players[turn].angle / 180.0 * PI;

	//double y_component = sin(angle) * players[turn].power * 0.2;
	//double x_component = cos(angle) * players[turn].power * 0.2;
	//force coord
	Coord2D force;
	force.Initialize(cos(angle) * players[turn].power * 0.2, sin(angle) * players[turn].power * 0.2);

	//double pNx;
	//double pNy;
	//declaring bombPos
	Coord2D bombPos;

	//negating x portion of force if it's right player's turn
	if (players[turn].s == RIGHT)
		force.xComponent *= -1;

	//double p0x = players[turn].col;
	//double p0y = g.ground.at(players[turn].col);
	// higher ground numbers are lower altitudes (0 is first line, etc).
	//p0y = lines - p0y;
	//tank position coord
	Coord2D tankPos;
	tankPos.Initialize(players[turn].col, lines - g.ground.at(players[turn].col));
	
	//I think I'll try defining gravity
	Coord2D gravity;
	gravity.Initialize(0, -0.98);

	for (int i = 1; i < 5000; i++)
	{
		//the larger the divisor, the smaller the interval between asterisks
		double di = i / 10.0;

		//pNx = (int)(p0x + di * x_component);
		//pNy = p0y + di * y_component + (di * di + di) * -0.98 / 2.0;
		//pNy = (int)(lines - pNy);
		//defining bombPos each time we come through the for loop
		bombPos = tankPos + force * di + gravity * 0.5 * (di * di + di);
		bombPos.yComponent = lines - bombPos.yComponent;

		//if (pNx < 1 || pNx >= cols - 2)
		if (bombPos.xComponent < 1 || bombPos.xComponent >= cols - 2)
			break;

		//if (pNy < 1) {
		if (bombPos.yComponent < 2)
		{
			//FIXME: change this const as needed for feeling
			Sleep(25);
			continue;
		}
		//this could be used if we don't use wind
	//	if (pNy >= lines - 2)
	//		break;

		//if (pNy > g.ground.at((int)pNx))
		//breaks out of loop if bomb would be below ground
		if (bombPos.yComponent > g.ground.at((int)bombPos.xComponent))
			break;

		//move((int)pNy - 1, (int)pNx + 1);
		move((int)bombPos.yComponent - 1, (int)bombPos.xComponent + 1);
		addch('*');
		refresh();
		//if(pNy)
		//hit detection goes here
		Sleep(25);
	}
	return false;
}

int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g;
	Player players[2];

	initscr();
	noecho();
	resize_term(lines, cols);
	keypad(stdscr, 1);

	g.InitializeGround();
	players[0].Initialize(rand() % (cols / 4), LEFT);
	players[1].Initialize(rand() % (cols / 4) + 3 * cols / 4 - 2, RIGHT);

	DrawScreen(g, players, turn);
	while (keep_going)
	{
		bool show_char = false;
		int c = getch();
		switch (c)
		{
		case 27:
			keep_going = false;
			break;

		case 's':
			players[turn].PowerDown();
			break;

		case 'w':
			players[turn].PowerUp();
			break;

		case 'd':
			players[turn].AngleUp();
			break;

		case 'a':
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
		case PADENTER:
			if (Shoot(g, players, turn) == true)
			{
				move(10, 10);
				addch('H');
			}
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
		DrawScreen(g, players, turn);
		if (show_char) {
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
	}
	erase();
	addstr("Hit any key to exit");
	refresh();
	getch();
	echo();
	endwin();
	return 0;
}