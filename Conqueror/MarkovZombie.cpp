#include <random>

#include "MarkovZombie.h"

MarkovZombie::MarkovZombie(Controller& controller, float color) : Character(controller, color)
{
	int r;
	int c;
	do {
		r = std::rand() % MAP_SIZE;
		c = std::rand() % MAP_SIZE;
	} while (controller.getData(r, c) == TERRITORY);

	pos[0] = c * STEP_SIZE;
	pos[1] = r * STEP_SIZE;
}

void MarkovZombie::move(int step) {
	if (step == 0) {
		int r;
		int c;
		do {
			r = row();
			c = col();
			// TODO : better random, markov chain, constantize
			float rand = (float)std::rand() / RAND_MAX;
			heading[1] = rand < 0.6f ? (Direction)((int)(rand / 0.15f) + 1) : heading[1];
			shift(c, r, heading[1]);
		} while (!controller.hasData(r, c) || controller.getData(r, c) > 0);
	}
	Character::move(step);
}
