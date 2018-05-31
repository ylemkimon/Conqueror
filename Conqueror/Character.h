#pragma once
#include "Constants.h"
#include "Controller.h"
#include "Color.h"

class Character {
protected:
	Controller& controller;
public:
	float color;
	int pos[2];
	Direction heading[2];

	int row();
	int col();
	int step();

	Character(Controller&, float);

	virtual void move(int);
	virtual void die();
	void changeHeading(Direction);
};