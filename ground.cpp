#include "curses.h"
#include "ground.hpp"

int lines = 40;
int cols = 120;
int base_height_divisor = 8;
int max_height_divisor = 2;

void Ground::InitializeGround()
{
	int current_height = lines - lines / base_height_divisor;
	int maximum_height = lines / max_height_divisor;

	for (int i = 1; i < cols - 1; i++) {
		int h = current_height;
		int r = rand() % 10000;
		if (r < 800) {
			current_height++;
			if (current_height >= lines - 2)
				current_height = lines - 2;
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
