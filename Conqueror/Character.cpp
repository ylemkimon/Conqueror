#include "Character.h"

#include <GL/glut.h>

void drawCircle(float cx, float cy) {
	float t;
	float x = 0.7f;
	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx, cy);
		for (int i = 0; i <= 100; i++) {
			glVertex2f(x + cx, y + cy);

			t = x;
			x = COS_PI_50 * x - SIN_PI_50 * y;
			y = SIN_PI_50 * t + COS_PI_50 * y;
		}
	glEnd();
}

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

void Character::draw() {
	Color shadowColor(color, .8f, .2f, 1);
	glColor4fv(shadowColor.rgba);
	drawCircle((float)pos[0] / STEP_SIZE + 0.65f, (float)pos[1] / STEP_SIZE + 0.35f);

	Color playerColor(color, .8f, .45f, 1);
	glColor4fv(playerColor.rgba);
	drawCircle((float)pos[0] / STEP_SIZE + 0.5f, (float)pos[1] / STEP_SIZE + 0.5f);
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
