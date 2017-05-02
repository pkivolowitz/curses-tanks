#if defined(WIN32)
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#endif

#include "ground.hpp"

int base_height_divisor = 8;
int max_height_divisor = 2;

void Ground::InitializeGround()
{
	int current_height = LINES - LINES / base_height_divisor;
	//int maximum_height = lines / max_height_divisor;

	for (int i = 1; i < COLS - 1; i++) {
		int h = current_height;
		int r = rand() % 10000;
		if (r < 800) {
			current_height++;
			if (current_height >= LINES - 2)
				current_height = LINES - 2;
		}
		else if (r < 1600) {
			current_height--;
			if (current_height < 1)
				current_height = 1;
		}
		ground.push_back(h);
	}
}

void Ground::Draw()
{
	for (size_t i = 0; i < ground.size(); i++) {
		mvaddch(ground.at(i), i + 1, '-');
	}
}
