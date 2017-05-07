
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

int MainMenu()
{
	int rv = 0;
	
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	//attron(COLOR_PAIR(1));
	WINDOW *w;
	w = newwin(10, 12, 1, 1);
	box(w, 0, 0);
	stringstream ss;
	ss = stringstream();
	move(LINES / 4, 30);
	ss << "Welcome to Tanks!";
	addstr(ss.str().c_str());
	ss = stringstream();
	move(LINES / 3, 20);
	ss << "Created by Nick Ressler & Eryn Benner";
	addstr(ss.str().c_str());
	ss = stringstream();
	move(LINES / 2, 24);
	ss << "Press The 'E' Key to Continue";
	addstr(ss.str().c_str());
	char c = getch();
	switch (c)
	{
	case 'e':
	case 'E':
		rv = 4;
		break;
	}
			//add a case where if none of the options are chosen nothing happens
			noecho();

	return rv;
}

//http://www.iforce2d.net/b2dtut/projected-trajectory

class Vec2D
{

};
void Shoot(Ground & g, Player * players, int turn, int bulleth, int bulletv)
{


	double angle = players[turn].angle / 180.0 * PI;
	//ver
	double y_component = sin(angle) * players[turn].power * 0.2;
	//hor
	double x_component = cos(angle) * players[turn].power * 0.2;

	double pNx;
	double pNy;

	
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

		
		if (pNy >= LINES - 2)
			break;

		//Bullet wont go through the ground
		if (pNy >= g.ground.at((int)pNx))
		{
			g.ground.at((int)pNx)++;

			g.ground.at((int)pNx - 1)++;

			g.ground.at((int)pNx + 1)++;
			break;
		}

		//No trail of bullets
		erase();

		DrawScreen(g, players, turn);

		move((int)pNy - 1, (int)pNx + 1);

		addch(ACS_LANTERN);

		refresh();
		// super fast
		if (players[turn].power >= 90)
		{
			Sleep(50);
		}
		//fast
		if(players[turn].power > 75 && players[turn].power < 90)
		{
			Sleep(90);
		}
		//average
		if(players[turn].power > 50 && players[turn].power < 75)
		{
			Sleep(125);
		}
		//slower
		if(players[turn].power > 25 && players[turn].power < 50)
		{
			Sleep(150);
		}
		//super slow
		if (players[turn].power <= 25)
		{
			Sleep(175);
		}
	
	}

	bulleth = pNx + 1;
	bulletv = pNy;

	stringstream ss;
	ss = stringstream();
	ss << "col: " << bulleth;
	move(1, COLS / 2 - 3);
	addstr(ss.str().c_str());
	refresh();

	ss = stringstream();
	ss << "line: " << bulletv;
	move(2, COLS / 2 - 3);
	addstr(ss.str().c_str());
	refresh();

	

	Sleep(1500);
	

	//makes it so if the bullet is within col of player 1, it will hit
	if (bulleth == players[0].col || bulleth == players[0].col + 1 || bulleth == players[0].col + 2 || bulleth == players[0].col - 1 || bulleth == players[0].col - 2)
	{
		if (bulletv == players[0].line || bulletv == players[0].line + 1 || bulletv == players[0].line + 2 || bulletv == players[0].line - 1 || bulletv == players[0].line - 2)
		{
	
		players[0].health--;
		}
	}

	//makes it so if the bullet is within col of player 2, it will hit
	if (bulleth == players[1].col || bulleth == players[1].col + 1 || bulleth == players[1].col + 2 || bulleth == players[1].col - 1 || bulleth == players[1].col - 2)
	{
		if (bulletv == players[1].line || bulletv == players[1].line + 1 || bulletv == players[1].line + 2 || bulletv == players[1].line - 1 || bulletv == players[1].line - 2)
		{
		
		players[1].health--;
		}
	}
	if (players[0].health == 0)
	{
		ss = stringstream();
		ss << "Player 1 is Dead! ";
		move(2, COLS / 5 - 3);
		addstr(ss.str().c_str());

		Sleep(1000);
		refresh();
	}
	if (players[1].health == 0)
	{
		ss = stringstream();
		ss << "Player 2 is Dead! ";
		move(2, COLS / 5 - 3);
		addstr(ss.str().c_str());

		Sleep(1000);
		refresh();
	}
}
	


int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g;
	Player players[2];
	
	initscr();
	
	while (true)
	{
		bool quit;
		quit = true;

		keypad(stdscr, 1);
	

		int x = 0;
		x = MainMenu();

		//quit
		if (x == 4)
		{
			quit = false;
			break;
		}
		
	}
	
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
