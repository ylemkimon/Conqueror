#include <ctime>
#include <fstream>

#include "Renderer.h"

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
	if (currentTime - previousTime < 16) {
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
	glutInitWindowSize(900, 900);
	glutCreateWindow("Conqueror");

	//glutGameModeString("1024x600:32@60");
	//glutEnterGameMode();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, MAP_SIZE + 1, -1, MAP_SIZE + 6);

	glClearColor(CLEAR_COLOR, 1);

	//int w, h;
	//unsigned int size, offset, headerSize;
	//std::ifstream infile("text.bmp", std::ios::binary);
	//infile.seekg(10);
	//infile.read((char *)&offset, 4);
	//infile.read((char *)&headerSize, 4);
	//infile.seekg(18);
	//infile.read((char *)&w, 4);
	//infile.read((char *)&h, 4);
	//size = w * h * 24;
	//unsigned char *data = new unsigned char[size];

	//infile.seekg(offset);
	//infile.read((char *)data, size);

	//int temp;
	//for (unsigned int i = 0; i < size; i += 3)
	//{
	//	temp = data[i];
	//	data[i] = data[i + 2];
	//	data[i + 2] = temp;
	//}

	//unsigned int texture_id;
	//glGenTextures(1, &texture_id);
	//glBindTexture(GL_TEXTURE_2D, texture_id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexImage2D(
	//	GL_TEXTURE_2D, 0, GL_RGB,
	//	256, 256, 0,
	//	GL_RGB, GL_UNSIGNED_BYTE,
	//	data
	//);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//renderer.texture_id = texture_id;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}
