#include "Player.h"

#include <GL/glut.h>

void drawCorner(int x, int y, Direction prev, Direction curr) {
	if (prev == LEFT || curr == LEFT) {
		x++;
	}
	if (prev == DOWN || curr == DOWN) {
		y++;
	}

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < 2; i++) {
			int _x = x;
			int _y = y;
			glVertex2i(_x, _y);
			shift(_x, _y, curr);
			glVertex2i(_x, _y);
			shift(_x, _y, prev);
			glVertex2i(_x, _y);
		}
	glEnd();
}

Player::Player(Controller &controller, float color) :
	Character(controller, color), trail(), base(), life(INITIAL_LIFE)
{
	pos[0] = CENTER_COORD;
	pos[1] = CENTER_COORD;
}

void Player::move(int step)
{
	Character::move(step);

	if (step == STEP_SIZE - 1) {
		int state = controller.getData(row(), col());
		if (state == 0) {
			updateTrail();
		}
		else if (state > 0) {
			if (!trail.empty()) {
				traverseTrail();
				trail.clear();

				controller.playSound("drop.wav");
			}
			base[0] = row();
			base[1] = col();
		}
	}
}

void Player::draw()
{
	if (!trail.empty()) {
		Color tailColor(color, .8f, .8f, .5f);
		glColor4fv(tailColor.rgba);

		Direction prev = NONE;
		int x = base[1];
		int y = base[0];
		for (const auto& move : trail) {
			if (prev != NONE) {
				drawCorner(x, y, prev, move.direction);
			}

			if (move.direction == UP || move.direction == RIGHT) {
				shift(x, y, move.direction);
			}
			if (move.length > 1) {
				int x1 = x;
				int y1 = y;
				shift(x, y, move.direction, move.length - 1);
				glRectf(x1, y1, x == x1 ? x + 1 : x, y == y1 ? y + 1 : y);
			}
			if (move.direction == DOWN || move.direction == LEFT) {
				shift(x, y, move.direction);
			}
			prev = move.direction;
		}
		if (prev == heading[0]) {
			glRectf(x, y, x + 1, y + 1);
		}
		else {
			drawCorner(x, y, prev, heading[0]);
		}
	}
	Character::draw();
}

void Player::die()
{
	pos[0] = CENTER_COORD;
	pos[1] = CENTER_COORD;
	heading[0] = NONE;
	heading[1] = NONE;
	trail.clear();
	for (int r = 0; r < MAP_SIZE; r++) {
		for (int c = 0; c < MAP_SIZE; c++) {
			if (controller.getData(r, c) < 0) {
				controller.setData(r, c, 0);
			}
		}
	}
	life--;
}

void Player::changeHeading(Direction newHeading)
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

void Player::updateTrail()
{
	if (trail.empty() || trail.back().direction != heading[0]) {
		trail.push_back(Segment{ heading[0], 0 });
	}
	trail.back().length++;
	controller.setData(row(), col(), TAIL);
}

void Player::traverseTrail()
{
	std::queue<int> queue[2];
	queue[0].push(base[0]);
	queue[1].push(base[1]);

	std::unordered_set<int> toFill;
	int value = TAIL - 1;

	bool first = true;
	while (!queue[0].empty()) {
		int r = queue[0].front();
		int c = queue[1].front();

		queue[0].pop();
		queue[1].pop();

		if (!first) {
			controller.setData(r, c, FILL);
		}
		else {
			first = false;
		}

		_traverseTrail(r + 1, c, value, queue, toFill);
		_traverseTrail(r - 1, c, value, queue, toFill);
		_traverseTrail(r, c + 1, value, queue, toFill);
		_traverseTrail(r, c - 1, value, queue, toFill);
	}

	for (int r = 0; r < MAP_SIZE; r++) {
		for (int c = 0; c < MAP_SIZE; c++) {
			int state = controller.getData(r, c);
			if (toFill.find(state) != toFill.end()) {
				controller.setData(r, c, FILL);
			}
			else if (state < 0) {
				controller.setData(r, c, 0);
			}
		}
	}
}

void Player::_traverseTrail(int r, int c, int &value, std::queue<int> *queue, std::unordered_set<int> &toFill) {
	if (!controller.hasData(r, c)) {
		return;
	}
	int state = controller.getData(r, c);
	if (state == 0) {
		if (fill(r, c, value)) {
			toFill.insert(value);
		}
		value--;
	}
	else if (state == TAIL) {
		queue[0].push(r);
		queue[1].push(c);
	}
}

bool Player::fill(int row, int col, int value) {
	bool closed = true;

	std::queue<int> queue[2];
	queue[0].push(row);
	queue[1].push(col);

	while (!queue[0].empty()) {
		int r = queue[0].front();
		int c = queue[1].front();

		queue[0].pop();
		queue[1].pop();

		if (!controller.hasData(r, c)) {
			closed = false;
			continue;
		}

		if (controller.getData(r, c) != 0) {
			continue;
		}

		controller.setData(r, c, value);

		queue[0].push(r + 1);
		queue[1].push(c);

		queue[0].push(r - 1);
		queue[1].push(c);

		queue[0].push(r);
		queue[1].push(c + 1);

		queue[0].push(r);
		queue[1].push(c - 1);
	}
	return closed;
}
