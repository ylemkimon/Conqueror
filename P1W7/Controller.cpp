#include <iostream>
#include <random>
#include <ctime>

#include "Controller.h"
#include "Player.h"

#include <GL/glut.h>

#define HUES_LEGNTH 24
static float HUES[HUES_LEGNTH] = { 0, .04f, .08f, .11f, .14f, .18f, .21f, .25f, .29f, .38f, .42f, .46f, .5f, .53f, .57f, .6f, .63f, .67f, .71f, .75f, .79f, .83f, .87f, .91f };

Controller::Controller() : step(), data(new int*[MAP_SIZE]), filled()
{
	std::srand(std::time(NULL));
	std::random_shuffle(HUES, HUES + HUES_LEGNTH);

	player = new Player(*this, HUES[0]);
	characters = { player };

	for (int i = 0; i < MAP_SIZE; i++) {
		data[i] = new int[MAP_SIZE]();
	}
	for (int i = -INITIAL_RANGE; i <= INITIAL_RANGE; i++) {
		for (int j = -INITIAL_RANGE; j <= INITIAL_RANGE; j++) {
			set((MAP_SIZE + 1) / 2 + i, (MAP_SIZE + 1) / 2 + j, TERRITORY);
		}
	}
}

Controller::~Controller()
{
	while (!characters.empty()) {
		delete characters.back();
		characters.pop_back();
	}

	for (int i = 0; i < MAP_SIZE; i++) {
		delete[] data[i];
	}
	delete[] data;
}

int Controller::get(int row, int col) const
{
	return data[row][col];
}

void Controller::set(int row, int col, int value)
{
	data[row][col] = value;
	if (value == TERRITORY) {
		filled++;
	}
}

bool Controller::isOutOfBounds(int row, int col) const
{
	return row < 0 || col < 0 || row >= MAP_SIZE || col >= MAP_SIZE;
}

Player* Controller::getPlayer()
{
	return player;
}

void Controller::updateFrame()
{
	for (const auto& character : characters) {
		character->move(step);
	}
	if (step == 0) {
		for (const auto& character : characters) {
			if (get(character->row(), character->col()) == TAIL && character->heading[0] != NONE) {
				player->die();
			}
		}
	}
	step = (step + 1) % STEP_SIZE;
}

void Controller::processSpecialKeys(int key, int x, int y)
{
	Direction heading = NONE;
	switch (key) {
	case GLUT_KEY_UP:
		heading = UP;
		break;
	case GLUT_KEY_DOWN:
		heading = DOWN;
		break;
	case GLUT_KEY_LEFT:
		heading = LEFT;
		break;
	case GLUT_KEY_RIGHT:
		heading = RIGHT;
		break;
	default:
		return;
	}
	player->changeHeading(heading);
}