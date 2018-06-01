#pragma once
#include "Character.h"

class MarkovZombie : public Character
{
public:
	MarkovZombie(Controller& controller, float color);
	virtual void move(int);
};
