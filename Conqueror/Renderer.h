#pragma once
#include "Constants.h"
#include "Controller.h"

class Renderer {
	Controller& controller;

	int bar_target;
public:
#ifdef USE_TEXTURE
	unsigned int texture_id;
#endif

	Renderer(Controller&);

	void draw();
	void drawBorder();
	void drawMap();
	void drawUI();
};
