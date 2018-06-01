#include "Player.h"

Player::Player(Controller &controller, float color) :
	Character(controller, color), trail(), base(), life(INITIAL_LIFE)
{
	pos[0] = CENTER_COORD;
	pos[1] = CENTER_COORD;
}

int* Player::getBase()
{
	return base;
}

std::vector<Segment>& Player::getTrail()
{
	return trail;
}

void Player::resetTrail() {
	trail.clear();
	for (int r = 0; r < MAP_SIZE; r++) {
		for (int c = 0; c < MAP_SIZE; c++) {
			if (controller.getData(r, c) < 0) {
				controller.setData(r, c, 0);
			}
		}
	}
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
				resetTrail();

				controller.playSound("drop.wav");
			}
			base[0] = row();
			base[1] = col();
		}
	}
}

void Player::die()
{
	pos[0] = CENTER_COORD;
	pos[1] = CENTER_COORD;
	heading[0] = NONE;
	heading[1] = NONE;
	resetTrail();
	life--;
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

		_traverseTrail(r + 1, c, queue);
		_traverseTrail(r - 1, c, queue);
		_traverseTrail(r, c + 1, queue);
		_traverseTrail(r, c - 1, queue);
	}
}

void Player::_traverseTrail(int r, int c, std::queue<int> *queue) {
	if (!controller.hasData(r, c)) {
		return;
	}
	int state = controller.getData(r, c);
	if (state == 0) {
		fill(r, c);
	}
	else if (state == TAIL) {
		queue[0].push(r);
		queue[1].push(c);
	}
}

void Player::fill(int row, int col) {
	bool closed = true;

	std::queue<int> queue[2];
	std::queue<int> toFill[2]; // TODO : use set instead of queue
	queue[0].push(row);
	queue[1].push(col);

	while (!queue[0].empty()) {
		int r = queue[0].front();
		int c = queue[1].front();

		queue[0].pop();
		queue[1].pop();

		if (!controller.hasData(r, c)) {
			closed = false;
			toFill[0] = {};
			toFill[1] = {};
			continue;
		}

		if (controller.getData(r, c) != 0) {
			continue;
		}

		controller.setData(r, c, VISITED);

		if (closed) {
			toFill[0].push(r);
			toFill[1].push(c);
		}

		queue[0].push(r + 1);
		queue[1].push(c);

		queue[0].push(r - 1);
		queue[1].push(c);

		queue[0].push(r);
		queue[1].push(c + 1);

		queue[0].push(r);
		queue[1].push(c - 1);
	}

	while (!toFill[0].empty()) {
		int r = toFill[0].front();
		int c = toFill[1].front();

		toFill[0].pop();
		toFill[1].pop();

		controller.setData(r, c, FILL);
	}
}
