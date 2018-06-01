#pragma once

/** Whether to use texture, comment this out if image loading fails */
#define USE_TEXTURE

/** Interval between frames in milliseconds */
#define FRAME_INTERVAL 16

/** The size of map, the number of cells in a row or column */
#define MAP_SIZE 81

/** The size of player's initial area around center */
#define INITIAL_RANGE 3

/** The size of shadow under the block */
#define SHADOW_SIZE 0.3f

/** The width of heart */
#define HEART_WIDTH 4

/** The number of steps to move from one cell to another */
#define STEP_SIZE 5

/** The coordinate of the center of the map */
#define CENTER_COORD (MAP_SIZE / 2 * STEP_SIZE)

/** The maximum coordinate of the map */
#define MAX_COORD ((MAP_SIZE - 1) * STEP_SIZE)

/** To-be-player's-territory cell state */
#define FILL 1

/** Player territory cell state */
#define TERRITORY 19

/** Tail cell state */
#define TAIL -1

/** Win game state(step) */
#define WIN -2

/** Lose game state(step) */
#define LOSE -3

/** Background(clear) color */
#define CLEAR_COLOR 1, 0.9804f, 0.8039f

/** cos pi/50 */
#define COS_PI_50 0.99802672842827156

/** sin pi/50 */
#define SIN_PI_50 0.06279051952931338

/** The number of player's live */
#define INITIAL_LIFE 3

/** The number of zombies */
#define ZOMBIE_COUNT 5

/** Minumum ratio to win */
#define WIN_CONDITION 0.9f

const float BOUNCE[TERRITORY + 1] = { .7f, .6f, .5f, .4f, .3f, .2f, .1f, 0, .1f, .2f, .3f, .4f, .3f, .2f, .1f, 0, .1f, .2f, .1f, 0 };

/** Border color */
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
