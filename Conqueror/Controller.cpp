/** @file Controller.cpp */

#include <random>
#include <ctime>

#include "Controller.h"
#include "Player.h"
#include "MarkovZombie.h"

#include <GL/glut.h>

/** The number of possible character colors */
#define HUES_LEGNTH 12

/** The hue of possible character colors */
static float HUES[HUES_LEGNTH] = { 0, .08f, .14f, .21f, .29f, .42f, .5f, .57f, .63f, .71f, .79f, .91f };

Controller::Controller() : step(), data(), filled()
{
	std::srand(unsigned(std::time(NULL)));
	std::random_shuffle(HUES, HUES + HUES_LEGNTH);

	for (int i = -INITIAL_RANGE; i <= INITIAL_RANGE; i++) {
		for (int j = -INITIAL_RANGE; j <= INITIAL_RANGE; j++) {
			setData(MAP_SIZE / 2 + i, MAP_SIZE / 2 + j, TERRITORY);
		}
	}

	player = new Player(*this, HUES[0]);
	characters = { player };
	for (int i = 0; i < ZOMBIE_COUNT; i++) {
		characters.push_back(new MarkovZombie(*this, HUES[i + 1]));
	}

#ifdef USE_SOUND
	SoundEngine = irrklang::createIrrKlangDevice();
	SoundEngine->play2D("music.wav", true);
#endif
}

Controller::~Controller()
{
	while (!characters.empty()) {
		delete characters.back();
		characters.pop_back();
	}
}

bool Controller::hasData(int row, int col) const
{
	return row >= 0 && col >= 0 && row < MAP_SIZE && col < MAP_SIZE;
}

int Controller::getData(int row, int col) const
{
	return data[row][col];
}

void Controller::setData(int row, int col, int value)
{
	data[row][col] = value;
	if (value == TERRITORY) {
		filled++;
	}
}

void Controller::playSound(const char* filename)
{
#ifdef USE_SOUND
	SoundEngine->play2D(filename);
#endif
}

Player* Controller::getPlayer()
{
	return player;
}

void Controller::updateFrame()
{
	if (step < 0) {
		return;
	}
	for (const auto& character : characters) {
		character->move(step);
	}
	if (step == 0) {
		int r = player->row();
		int c = player->col();
		for (const auto& character : characters) {
			int cr = character->row();
			int cc = character->col();
			if ((data[cr][cc] == TAIL && character->heading[0] != NONE) || // tail hit
				(character != player && cr == r && cc == c)) { // collide with zombie
				player->die();
				playSound("death.wav");
			}
		}
		if (player->life == 0) {
			step = LOSE;
			playSound("gameover.wav");
			return;
		}
	}
	else if (step == STEP_SIZE - 1) {
		std::vector<Character*>::iterator it = characters.begin();
		while (it != characters.end()) {
			if (*it != player && data[(*it)->row()][(*it)->col()] > 0) { // zombie in the new territory
				it = characters.erase(it);
				playSound("kill.wav");
			}
			else {
				++it;
			}
		}
		if ((float)filled / (MAP_SIZE * MAP_SIZE) > WIN_CONDITION) {
			step = WIN;
			playSound("win.wav");
			return;
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