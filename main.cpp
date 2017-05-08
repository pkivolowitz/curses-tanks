
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
	refresh();
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

	//Welcome to Tanks! Sign//
	ss << " _    _      _                            _          _____           _        _";
	mvaddstr(1, COLS /2 - 42, ss.str().c_str());

	ss = stringstream();
	ss << "| |  | |    | |                          | |        |_   _|         | |      | |";
	mvaddstr(2, COLS / 2 - 42, ss.str().c_str());

	ss = stringstream();
	ss << "| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___     | | __ _ _ __ | | _____| |";
	mvaddstr(3, COLS / 2 - 42, ss.str().c_str());

	ss = stringstream();
	ss << "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\    | |/ _` | '_ \\| |/ / __| |";
	mvaddstr(4, COLS / 2 - 42, ss.str().c_str());

	ss = stringstream();
	ss << "\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |   | | (_| | | | |   <\\__ \\_|";
	mvaddstr(5, COLS / 2 - 42, ss.str().c_str());

	ss = stringstream();
	ss << " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/    \\_/\\__,_|_| |_|_|\\_\\___(_)";
	mvaddstr(6, COLS / 2 - 42, ss.str().c_str());

	//Created by Sign//
	
	ss = stringstream();
	ss << "  ___              _          _   _         ";
	mvaddstr(8, COLS / 2 - 24,ss.str().c_str());

	ss = stringstream();
	ss << " / __|_ _ ___ __ _| |_ ___ __| | | |__ _  _ ";
	mvaddstr(9, COLS / 2 - 24, ss.str().c_str());
	
	ss = stringstream();
	ss << "| (__| '_/ -_) _` |  _/ -_) _` | | '_ \\ || |";
	mvaddstr(10, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	ss << " \\___|_| \\___\\__,_|\\__\\___\\__,_| |_.__/\\_, |";
	mvaddstr(11, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	ss << "                                       |__/ ";
	mvaddstr(12, COLS / 2 - 24, ss.str().c_str());

	//Nick Ressler Sign//

	ss = stringstream();
	ss << " _  _ _    _     ___           _         ";
	mvaddstr(13, COLS / 2 - 23, ss.str().c_str());

	ss = stringstream();
	ss << "| \\| (_)__| |__ | _ \\___ _____| |___ _ _ ";
	mvaddstr(14, COLS / 2 - 23, ss.str().c_str());

	ss = stringstream();
	ss << "| .` | / _| / / |   / -_|_-<_-< / -_) '_|";
	mvaddstr(15, COLS / 2 - 23, ss.str().c_str());

	ss = stringstream();
	ss << "|_|\\_|_\\__|_\\_\\ |_|_\\___/__/__/_\\___|_|  ";
	mvaddstr(16, COLS / 2 - 23, ss.str().c_str());

	//& Sign//

	ss = stringstream();
	ss << " __     ";
	mvaddstr(17, COLS / 2 - 4, ss.str().c_str());

	ss = stringstream();
	ss << "/ _|___ ";
	mvaddstr(18, COLS / 2 - 4, ss.str().c_str());

	ss = stringstream();
	ss << "> _|_ _|";
	mvaddstr(19, COLS / 2 - 4, ss.str().c_str());

	ss = stringstream();
	ss << "\\_____| ";
	mvaddstr(20, COLS / 2 - 4, ss.str().c_str());

	//Eryn Benner Sign//

	ss = stringstream();
	ss << " ___                 ___                        ";
	mvaddstr(21, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	ss << "| __|_ _ _  _ _ _   | _ ) ___ _ _  _ _  ___ _ _ ";
	mvaddstr(22, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	ss << "| _|| '_| || | ' \\  | _ \\/ -_) ' \\| ' \\/ -_) '_|";
	mvaddstr(23, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	ss << "|___|_|  \\_, |_||_| |___/\\___|_||_|_||_\\___|_|  ";
	mvaddstr(24, COLS / 2 - 24, ss.str().c_str());

	ss = stringstream();
	move(LINES - 2, 43);
	ss << "Press The ENTER to Continue";
	addstr(ss.str().c_str());

	char c = getch();
	if(c == 10)
		rv = 4;
	
	//add a case where if none of the options are chosen nothing happens

	noecho();
	return rv;
}

bool hit = false;
/*
int HitBox(int P1 , int shotl, int shotc, int turn)
{
	
	if (turn == 0)
	{
		if (shotl > players + LINES + 1 || shotl < P1 - LINES - 1)
		{

		}
		if (shotc > P1 + COLS + 1 || shotc > P1 - COLS - 1)
		{

		}
	}
}
*/
//http://www.iforce2d.net/b2dtut/projected-trajectory

class Vec2D
{

};
void Shoot(Ground & g, Player * players, int turn, double bulleth, double bulletv, bool hit)
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
		//this makes the bullet only one
		erase();
		DrawScreen(g, players, turn);
		mvaddch((int)pNy - 1, (int)pNx + 1, ACS_LANTERN);

		refresh();

		// super fast
		if (players[turn].power >= 90)
		{
			Sleep(50);
		}

		//fast
		if (players[turn].power > 75 && players[turn].power <= 90)

		{
			Sleep(90);
		}

		//average
		if (players[turn].power > 50 && players[turn].power <= 75)

		{
			Sleep(125);
		}

		//slower
		if (players[turn].power > 25 && players[turn].power <= 50)

		{
			Sleep(150);
		}

		//super slow
		if (players[turn].power <= 25)

		{
			Sleep(175);
		}

		bulleth = pNx; //y
		bulletv = pNy; //x

		//if bomb is within 1 column in either direction of player 1 or on the column
		//                         line - 1                           
		//                             ^
		//             |           ____|__
		// col - 1 <-- |                  |
		//		       |_______           | --> col + 1
		//                 |              |
		//                 V
		//               line + 1
		/*if (bulletv >= players[0].col - 1 && bulleth <= players[0].line + 1 || bulletv <= players[0].col + 1 && bulleth >= players[0].col - 1)
		{
			hit = true;
			break;
		}
		if (hit == true)
			players[0].health--;
		if (bulletv >= players[1].col - 1 && bulleth <= players[1].line + 1 || bulletv <= players[1].col + 1 && bulleth >= players[1].col - 1)
		{
			hit = true;
			break;
		}
		if (hit == true)
			players[1].health--;*/

	}
	//Testing bullet coordinates//
	stringstream ss;
	ss = stringstream();
	ss << "col: " << bulleth;

	mvaddstr(1, COLS / 2 - 3, ss.str().c_str());
	refresh();

	ss = stringstream();
	ss << "line: " << bulletv;

	mvaddstr(2, COLS / 2 - 3, ss.str().c_str());
	refresh();

	ss = stringstream();
	ss << "#";
	mvaddstr(bulletv, bulleth, ss.str().c_str());
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

		case KEY_DOWN:
			players[turn].PowerDown();
			break;

		case KEY_UP:
			players[turn].PowerUp();
			break;

		case KEY_RIGHT:
			players[turn].AngleUp();
			break;

		case KEY_LEFT:
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn, bulleth, bulletv, hit);
			//HitBox(players[1].Initialize(), )
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
		DrawScreen(g, players, turn);
		if (show_char) {
			stringstream ss;
			ss << setw(4) << c << " ";
			mvaddstr(0, 1, ss.str().c_str());
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
