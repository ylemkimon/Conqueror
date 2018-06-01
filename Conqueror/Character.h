#pragma once
#include "Constants.h"
#include "Controller.h"
#include "Color.h"

class Character {
protected:
	Controller& controller;
	int pos[2];
public:
	float color;
	Direction heading[2];

	int row();
	int col();
	int step();

	Character(Controller&, float);

	virtual void move(int);
	virtual void draw();
};
