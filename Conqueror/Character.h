#pragma once
#include "Constants.h"
#include "Controller.h"
#include "Color.h"

class Character {
protected:
	Controller& controller;
public:
	int pos[2];
	Direction heading[2];
	float color;

	int row();
	int col();
	int step();

	Character(Controller&, float);

	virtual void move(int);
	void changeHeading(Direction);
};