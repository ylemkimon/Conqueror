#include "Renderer.h"
#include "Segment.h"
#include "Player.h"

#include <GL/glut.h>

void drawHeart(int x) {
	glRectf(x + .5f, MAP_SIZE + 5, x + 1.5f, MAP_SIZE + 4.5f);
	glRectf(x + 2, MAP_SIZE + 5, x + 3, MAP_SIZE + 4.5f);
	glRectf(x, MAP_SIZE + 4.5f, x + 3.5f, MAP_SIZE + 3);
	glRectf(x + .5f, MAP_SIZE + 3, x + 3, MAP_SIZE + 2.5f);
	glRectf(x + 1, MAP_SIZE + 2.5f, x + 2.5f, MAP_SIZE + 2);
	glRectf(x + 1.5f, MAP_SIZE + 2, x + 2, MAP_SIZE + 1.5f);
}

Renderer::Renderer(Controller &controller) : controller(controller), bar_target()
{
}

void Renderer::draw()
{
	drawBorder();
	drawMap();
	for (const auto& character : controller.characters) {
		character->draw();
	}
	drawUI();
}

void Renderer::drawBorder()
{
	glColor3fv(BORDER_COLOR);
	glRectf(-1, -1, 0, MAP_SIZE + 1);
	glRectf(MAP_SIZE, -1, MAP_SIZE + 1, MAP_SIZE + 1);
	glRectf(-1, -1, MAP_SIZE + 1, 0);
	glRectf(-1, MAP_SIZE, MAP_SIZE + 1, MAP_SIZE + 1);
}

void Renderer::drawMap()
{
	float hue = controller.getPlayer()->color;
	Color shadowColor(hue, .8f, .2f, 1);

	for (int r = MAP_SIZE - 1; r >= 0; r--) {
		for (int c = 0; c < MAP_SIZE; c++) {
			int state = controller.getData(r, c);
			if (state <= 0) {
				continue;
			}
			float y = r + BOUNCE[state];

			int bottomState = controller.hasData(r - 1, c) ? controller.getData(r - 1, c) : TERRITORY;
			if ((state == TERRITORY) != (bottomState == TERRITORY) || bottomState <= 0) {
				glColor4fv(shadowColor.rgba);
				glRectf(c, y - SHADOW_SIZE, c + 1, y);
			}

			Color bounceColor(hue, .8f, .6f - BOUNCE[state] / 6, 1.f);
			glColor4fv(bounceColor.rgba);
			glRectf(c, y, c + 1, y + 1);

			if (state < TERRITORY) {
				controller.setData(r, c, state + 1);
			}
		}
	}
}

void Renderer::drawUI()
{
	Player& p = *controller.getPlayer();

	glColor3f(1, 0, 0);
	for (int i = 0; i < INITIAL_LIFE; i++) {
		if (i == p.life) {
			glColor3f(.2f, .2f, .2f);
		}
		drawHeart(HEART_WIDTH * i);
	}
	int start = HEART_WIDTH * INITIAL_LIFE + 1;

	char buffer[10];
	int len = sprintf(buffer, "KILLS: %d", ZOMBIE_COUNT + 1 - controller.characters.size());
	int end = MAP_SIZE - len - 1;

	glColor3f(0, 0, 0);
	glRasterPos2f(end, MAP_SIZE + 2.5f);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
	}

	int diff = controller.filled - bar_target;
	if (diff > 0) {
		bar_target += diff < 80 ? (diff > 4 ? diff / 4 : 1) : 20;
	}
	float ratio = (float)bar_target / (MAP_SIZE * MAP_SIZE);
	float bar_length = ratio * (end - start);

	Color barColor(p.color, .8f, .4f, 1);
	glColor4fv(barColor.rgba);
	glRectf(start, MAP_SIZE + 1.5f, start + bar_length, MAP_SIZE + 5);

	len = sprintf(buffer, "%.2f %%", ratio * 100);
	if (bar_length < len + 1.3f) {
		glRasterPos2f(start + bar_length + .8f, MAP_SIZE + 2.5f);
	}
	else {
		glColor3f(1, 1, 1);
		glRasterPos2f(start + bar_length - len - 1.2f, MAP_SIZE + 2.5f);
	}
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
	}

	if (controller.step < 0) {
		glColor4f(.2f, .2f, .2f, .5f);
		glRectf(-1, -1, MAP_SIZE + 1, MAP_SIZE + 6);

#ifdef USE_TEXTURE
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id);
#endif

		float quarter = (float)MAP_SIZE / 4;
		float texture_offset = 0;
		
		if (controller.step == LOSE) {
			texture_offset = .5f;
			glColor3f(1, 0, 0);
		}
		else {
			glColor3f(0, 0, 1);
		}

		glBegin(GL_POLYGON);
			glTexCoord2f(0, texture_offset + .5f); glVertex2f(quarter, 2 * quarter);
			glTexCoord2f(0, texture_offset); glVertex2f(quarter, 3 * quarter);
			glTexCoord2f(1, texture_offset); glVertex2f(3 * quarter, 3 * quarter);
			glTexCoord2f(1, texture_offset + .5f); glVertex2f(3 * quarter, 2 * quarter);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}
