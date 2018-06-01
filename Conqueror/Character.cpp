#include "Character.h"

Character::Character(Controller& controller, float color) :
	controller(controller), color(color), pos(), heading()
{
}

void Character::move(int step)
{
	if (this->step() != step) {
		return;
	}
	if (step == 0) {
		heading[0] = heading[1];

		if ((pos[0] == 0 && heading[0] == LEFT) || (pos[0] == MAX_COORD && heading[0] == RIGHT) ||
			(pos[1] == 0 && heading[0] == DOWN) || (pos[1] == MAX_COORD && heading[0] == UP)) {
			heading[0] = NONE;
			heading[1] = NONE;
			return;
		}
	}
	shift(pos[0], pos[1], heading[0]);
}

void Character::die() // TODO : explosion effect, otherwise remove
{
}

void Character::changeHeading(Direction newHeading) // TODO : move to Player
{
	if (heading[0] == NONE) {
		int r = row();
		int c = col();
		shift(c, r, newHeading);
		if (!controller.hasData(r, c) || controller.getData(r, c) == TAIL) {
			return;
		}
	}
	else if ((heading[0] == UP || heading[0] == DOWN) == (newHeading == UP || newHeading == DOWN)) {
		return;
	}
	heading[1] = newHeading;
}

int Character::row()
{
	return pos[1] / STEP_SIZE + (pos[1] % STEP_SIZE != 0 && heading[0] == UP);
}

int Character::col()
{
	return pos[0] / STEP_SIZE + (pos[0] % STEP_SIZE != 0 && heading[0] == RIGHT);
}

int Character::step()
{
	switch (heading[0]) {
	case LEFT:
		return (MAX_COORD - pos[0]) % STEP_SIZE;
	case RIGHT:
		return pos[0] % STEP_SIZE;
	case UP:
		return pos[1] % STEP_SIZE;
	case DOWN:
		return (MAX_COORD - pos[1]) % STEP_SIZE;
	default:
		return 0;
	}
}
