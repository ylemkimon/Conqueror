#pragma once
#define MAP_SIZE 81
#define INITIAL_RANGE 3

#define SHADOW_SIZE 0.3f
#define UI_SIZE 8

#define STEP_SIZE 5

#define MAX_COORD ((MAP_SIZE - 1) * STEP_SIZE)

#define TERRITORY 19
#define TAIL -1
#define VISITED -2

#define CLEAR_COLOR 1, 0.9804f, 0.8039f

#define COS_PI_50 0.99802672842827156
#define SIN_PI_50 0.06279051952931338

const float BOUNCE[TERRITORY + 1] = { .7f, .6f, .5f, .4f, .3f, .2f, .1f, 0, .1f, .2f, .3f, .4f, .3f, .2f, .1f, 0, .1f, .2f, .1f, 0 };

const float BORDER_COLOR[] = { .8275f, .8275f, .8275f };

enum Direction { NONE, UP, RIGHT, DOWN, LEFT };

inline void shift(int& x, int& y, Direction direction, int delta = 1) {
	switch (direction) {
	case UP:
		y += delta;
		break;
	case RIGHT:
		x += delta;
		break;
	case DOWN:
		y -= delta;
		break;
	case LEFT:
		x -= delta;
		break;
	}
}