#include <iostream>
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
#include "Vec2d.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(WIN32)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

void Instructions()
{
	move(0, 0);
	addstr("Game Instructions:");
	move(2, 0);
	addstr("To increase Power press w");
	move(4, 0);
	addstr("To decrease Power press s");
	move(6, 0);
	addstr("To increase the Angle press d");
	move(8, 0);
	addstr("To decrease the Angle press a");
	move(10, 0);
	addstr("To shoot press enter");
	move(12, 0);
	addstr("To give up your shot and move right double press x");
	move(14, 0);
	addstr("To give up your shot and move left double press z");
	move(16, 0);
	addstr("Press c to continue to the game.");
	refresh();
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

void Shoot(Ground & g, Player * players, int turn)
{
	bool rv = false;
	bool hi = false;
	int enemy = 1 - turn;
	double angle = players[turn].angle / 180.0 * PI;

	Vec2d p0(players[turn].col, g.ground.at(players[turn].col) - 1);
	Vec2d force(cos(angle) * players[turn].power * 0.2, sin(angle) * players[turn].power * 0.2);
	Vec2d gravity(0, -0.98);
	
	double time_divisor = 15.0;
	
	if (players[turn].s == RIGHT)
		force.x = -force.x;
	double x = 0.0;
	double y = 0.0;
	// higher ground numbers are lower altitudes (0 is first line, etc).
	p0.y = LINES - p0.y;
	for (int i = 1; i < 5000; i++)
	{
		double di = i / time_divisor;

		Vec2d pN(x, y);
		pN.x = (int)(p0.x + di * force.x);
		pN.y = p0.y + di * force.y + (di * di + di) * -9.8 / time_divisor / 1.5;
		pN.y = (int)(LINES - pN.y);



		if (players[enemy].col == pN.x && g.ground.at(players[enemy].col) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col + 1 == pN.x && g.ground.at(players[enemy].col) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col - 1 == pN.x && g.ground.at(players[enemy].col) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col == pN.x && g.ground.at(players[enemy].col + 1) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col == pN.x && g.ground.at(players[enemy].col - 1) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col + 1 == pN.x && g.ground.at(players[enemy].col + 1) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col + 1 == pN.x && g.ground.at(players[enemy].col - 1) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col - 1 == pN.x && g.ground.at(players[enemy].col - 1) == pN.y)
		{
			rv = true;
			break;
		}
		else if (players[enemy].col - 1 == pN.x && g.ground.at(players[enemy].col + 1) == pN.y)
		{
			rv = true;
			break;
		}
		//hitting yourself
		else if (players[turn].col == pN.x && g.ground.at(players[turn].col) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col + 1 == pN.x && g.ground.at(players[turn].col) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col - 1 == pN.x && g.ground.at(players[turn].col) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col == pN.x && g.ground.at(players[turn].col + 1) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col == pN.x && g.ground.at(players[turn].col - 1) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col + 1 == pN.x && g.ground.at(players[turn].col + 1) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col + 1 == pN.x && g.ground.at(players[turn].col - 1) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col - 1 == pN.x && g.ground.at(players[turn].col - 1) == pN.y)
		{
			hi = true;
			break;
		}
		else if (players[turn].col - 1 == pN.x && g.ground.at(players[turn].col + 1) == pN.y)
		{
			hi = true;
			break;
		}

		if (pN.x < 1 || pN.x >= COLS - 2)
			break;
		if (pN.y < 1) 
			{
				MySleep(50);
				continue;
			}
		if (pN.y >= LINES - 2)
			break;
		if (pN.y > g.ground.at((int)pN.x))
			break;

		if (pN.y == g.ground.at((int)pN.x))
			g.ground.at((int)pN.x) = g.ground.at((int)pN.x) + 1;

		move((int)pN.y - 1, (int)pN.x + 1);
		addch('*');
		refresh();
		MySleep(50);
	}
	if (rv == true)
	{
		players[enemy].Health();
		g.ground.erase(g.ground.begin(), g.ground.end());
		g.InitializeGround();
		DrawScreen(g, players, turn);
	}
	if (hi == true)
	{
		players[turn].Health();
		g.ground.erase(g.ground.begin(), g.ground.end());
		g.InitializeGround();
		DrawScreen(g, players, turn);
	}
}

void Move(Player *players, Ground &g, int turn)
{
	int c = getch();
	if (c == 'x')
	{
		if (players[turn].col > COLS - 6)
		{
			players[turn].col = players[turn].col;
		}
		//move right
		else
		{
			players[turn].col = players[turn].col + 2;
		}

	}
	else if (c == 'z')
	{
		if (players[turn].col < 3)
		{
			players[turn].col = players[turn].col;
		}
		//move left
		else
		{
			players[turn].col = players[turn].col - 2;
		}
		
	}
}

int main(int argc, char * argv[])
{
	
	srand((unsigned int)time(nullptr));
	int turn = 0;
	bool keep_going = true;
	bool r = true;
	Ground g;
	Player players[2];

	initscr();
	noecho();
	keypad(stdscr, 1);
	
	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);

	while (r)
	{
		Instructions();
		int s = getch();
		if (s == 'c')
			r = false;
	}

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

		case 'z':
			Move(players, g, turn);
			turn = 1 - turn;
			break;

		case 'x':
			Move(players, g, turn);
			turn = 1 - turn;
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn);
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
		
		DrawScreen(g, players, turn);

		if (show_char)
		{
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
		if (players[turn].health == 0 || players[1 - turn].health == 0)
		{
			erase();
			move(COLS / 2, LINES / 2);
			addstr("Would you like to play again? y or n");
			refresh();
			int a = getch();

			if (a == 'y')
			{
				players[0].health = 3;
				players[1].health = 3;
				players[turn].Wins();
				g.ground.erase(g.ground.begin(), g.ground.end());
				g.InitializeGround();				
				DrawScreen(g, players, turn);
				continue;
			}
			else if (a == 'n')
				keep_going = false;
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
