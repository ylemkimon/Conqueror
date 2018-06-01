#include <ctime>
#include <fstream>

#include "Renderer.h"

#ifdef USE_TEXTURE
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#endif

#include <GL/glut.h>

Controller controller;
Renderer renderer(controller);

void processSpecialKeys(int key, int x, int y) {
	controller.processSpecialKeys(key, x, y);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.draw();
	glutSwapBuffers();
}

void idle() {
	static clock_t previousTime = clock();
	clock_t currentTime = clock();
	if (currentTime - previousTime < FRAME_INTERVAL) {
		return;
	}
	previousTime = currentTime;

	controller.updateFrame();

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(150, 100);
	glutInitWindowSize(830, 880);
	glutCreateWindow("Conqueror");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, MAP_SIZE + 1, -1, MAP_SIZE + 6);

	glClearColor(CLEAR_COLOR, 1);

#ifdef USE_TEXTURE
	int w, h, comp;
	unsigned char* image = stbi_load("text.png", &w, &h, &comp, STBI_rgb_alpha);

	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		w, h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE,
		image
	);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	renderer.texture_id = texture_id;

	stbi_image_free(image);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}
