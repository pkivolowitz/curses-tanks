
#include <iostream> //Eryn Benner// & // Nick Ressler
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#if defined(WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#include <unistd.h>
#endif

#include "ground.hpp"
#include "player.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(_WIN32)
	Sleep(milliseconds);
#endif
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

}
void MainMenu()
{

	start_color();
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	//attron(COLOR_PAIR(1));
	stringstream ss;
	ss = stringstream();
	move(LINES / 3, 17);
	ss << "Welcome to Tanks!";
	
	addstr(ss.str().c_str());
	noecho();
	refresh();
}

//http://www.iforce2d.net/b2dtut/projected-trajectory

class Vec2D
{

};
void Shoot(Ground & g, Player * players, int turn, int bulleth, int bulletv)
{


	double angle = players[turn].angle / 180.0 * PI;
	//vertical
	double y_component = sin(angle) * players[turn].power * 0.2;
	//horizontal
	double x_component = cos(angle) * players[turn].power * 0.2;

	double pNx;
	double pNy;

	//flips the bullet if it's the player on the other side of the screen
	if (players[turn].s == RIGHT)
		x_component = -x_component;

	double p0x = players[turn].col;
	double p0y = g.ground.at(players[turn].col);
	// higher ground numbers are lower altitudes (0 is first line, etc).

	p0y = LINES - p0y;


	for (int i = 1; i < 5000; i++)
	{
		double di = i / 5.0;

		pNx = (int)(p0x + di * x_component);
		pNy = p0y + di * y_component + (di * di + di) * -0.98 / 2.0;
		pNy = (int)(LINES - pNy);
		//if it goes too far left or too far right this ends the turn
		if (pNx < 1 || pNx >= COLS - 2)
			break;
		//if this goes off the screen upwards it just sleeps until the bomb comes back in
		if (pNy < 1) {
			Sleep(50);
			continue;
		}

		//if bullet goes off the screen at the bottom
		if (pNy >= LINES - 2)
			break;



		//this makes the bullet only one
		erase();
		DrawScreen(g, players, turn);
		move((int)pNy - 1, (int)pNx + 1);
		addch(ACS_LANTERN);


		refresh();
		Sleep(100);
	}
	//if bomb is within 1 column in either direction of player 1 or on the column
	if (bulleth == players[0].col || bulleth == players[0].col + 1 || bulleth == players[0].col - 1)
	{
		if (bulletv == players[0].line || bulletv == players[0].line + 1 || bulletv == players[0].line - 1)
		{
			players->health--;
		}
	}
	//if bomb is within 1 column in either direction of player 2
	if (bulleth == players[1].col || bulleth == players[1].col + 1 || bulleth == players[1].col - 1)
	{
		if (bulletv == players[1].line || bulletv == players[1].line + 1 || bulletv == players[1].line - 1)
		{
			players->health--;
		}

}
	bulleth = pNx + 1;
	bulletv = pNy - 1;

	stringstream ss;
	ss = stringstream();
	ss << "col: " << bulleth;
	move(2, COLS / 2 - 5);
	addstr(ss.str().c_str());
	refresh();

	ss = stringstream();
	ss << "line: " << bulletv;
	move(3, COLS / 2 - 5);
	addstr(ss.str().c_str());
	refresh();

	ss = stringstream();
	ss << "#";
	move(bulletv, bulleth);
	addstr(ss.str().c_str());
	refresh();

	Sleep(1200);
}
int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g;
	Player players[2];
	
	initscr();
	/*
	while (true)
	{
		char quit 
		char x = getch();
		
		

			MainMenu();
		
	}
	*/
	clear();
	keypad(stdscr, 1);
	int bulleth = 0;
	int bulletv = 0;
	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);

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

		case 'w':
			players[turn].PowerDown();
			break;

		case 's':
			players[turn].PowerUp();
			break;

		case 'a':
			players[turn].AngleUp();
			break;

		case 'd':
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn, bulleth, bulletv);
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
	/*
	erase();
	addstr("Hit any key to exit");
	refresh();
	getch();
	echo();
	endwin();
	return 0;
	*/
	return 0;
}
