#pragma once
#include "Character.h"

class Zombie : public Character
{
public:
	Zombie(Controller& controller, float color);
	virtual void move(int);
};

