// cin with strings

#include "GL\freeglut.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
const int width = 800;
const int height = 600;
char v = 0;
char f = 0;
int nV = 0;
int nF = 0;
int hasNormal = 0;
int k = 0;
int h = 0;
int z = 0;
int x = 0;
int g = 0;
float vertices[10086][6];
float originalV[10086][6];
int faces[10086][3];
int menuX = -1;
int menuY = -1;
int menuZ = -1;
float scalef = 1.0;
float matrix1[16], matrix2[16];

void draw_pic() {
	glBegin(GL_TRIANGLES);
	for (int j = 0; j < nF; j++) {
		glColor3f(1, 1, 1);
		glVertex3f(vertices[faces[j][0] - 1][0],
			vertices[faces[j][0] - 1][1],
			vertices[faces[j][0] - 1][2]);

		glColor3f(0, 0, 0);
		glVertex3f(vertices[faces[j][1] - 1][0],
			vertices[faces[j][1] - 1][1],
			vertices[faces[j][1] - 1][2]);

		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(vertices[faces[j][2] - 1][0],
			vertices[faces[j][2] - 1][1],
			vertices[faces[j][2] - 1][2]);
	}
	glEnd();
}
void mouse(int button, int state, int x, int y){

	if ((button == 3) || (button == 4)){
		if (button == 3) {
			scalef += 0.01;
		}
		else {
			scalef -= 0.01;
		}
	}
}
static void display() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(matrix1);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(matrix1);
	switch (menuX)
	{
	case 0:
		glRotatef(-90, 1, 0, 0);
		//std::cout << "here2222\n";
		menuX = -1;
		break;
	case 1:
		glRotatef(-45, 1, 0, 0);
		menuX = -1;
		break;
	case 2:
		glRotatef(-15, 1, 0, 0);
		menuX = -1;
		break;
	case 3:
		glRotatef(-5, 1, 0, 0);
		menuX = -1;
		break;
	case 4:
		glRotatef(0, 1, 0, 0);
		menuX = -1;
		break;
	case 5:
		glRotatef(5, 1, 0, 0);
		menuX = -1;
		break;
	case 6:
		glRotatef(15, 1, 0, 0);
		menuX = -1;
		break;
	case 7:
		glRotatef(45, 1, 0, 0);
		menuX = -1;
		break;
	case 8:
		glRotatef(90, 1, 0, 0);
		menuX = -1;
		break;
	default:
		break;
	}
	switch (menuY)
	{
	case 0:
		glRotatef(-90, 0, 1, 0);
		menuY = -1;
		break;
	case 1:
		glRotatef(-45, 0, 1, 0);
		menuY = -1;
		break;
	case 2:
		glRotatef(-15, 0, 1, 0);
		menuY = -1;
		break;
	case 3:
		glRotatef(-5, 0, 1, 0);
		menuY = -1;
		break;
	case 4:
		glRotatef(0, 0, 1, 0);
		menuY = -1;
		break;
	case 5:
		glRotatef(5, 0, 1, 0);
		menuY = -1;
		break;
	case 6:
		glRotatef(15, 0, 1, 0);
		menuY = -1;
		break;
	case 7:
		glRotatef(45, 0, 1, 0);
		menuY = -1;
		break;
	case 8:
		glRotatef(90, 0, 1, 0);
		menuY = -1;
		break;
	default:
		break;
	}
	switch (menuZ)
	{
	case 0:
		glRotatef(-90, 0, 0, 1);
		menuZ = -1;
		break;
	case 1:
		glRotatef(-45, 0, 0, 1);
		menuZ = -1;
		break;
	case 2:
		glRotatef(-15, 0, 0, 1);
		menuZ = -1;
		break;
	case 3:
		glRotatef(-5, 0, 0, 1);
		menuZ = -1;
		break;
	case 4:
		glRotatef(0, 0, 0, 1);
		menuZ = -1;
		break;
	case 5:
		glRotatef(5, 0, 0, 1);
		menuZ = -1;
		break;
	case 6:
		glRotatef(15, 0, 0, 1);
		menuZ = -1;
		break;
	case 7:
		glRotatef(45, 0, 0, 1);
		menuZ = -1;
		break;
	case 8:
		glRotatef(90, 0, 0, 1);
		menuZ = -1;
		break;
	default:
		break;
	}
	glScalef(scalef, scalef, scalef);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix1);
	draw_pic();
	glutSwapBuffers();
}
static void menu_callback2(int menu) {
	menuX = menu;
}
static void menu_callback3(int menu) {
	menuY = menu;
}
static void menu_callback4(int menu) {
	menuZ = menu;
}
static void menu_callback(int menu) {
	if (menu == 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix2);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix1);
	}
	if (menu == 1) {
		//std::cout << " here0 \n";
		std::string s1;
		std::cout << "Enter the file name: ";
		getline(std::cin, s1);
		std::cout << "File is " << s1 << " \n";
		char buffer[256];
		std::ifstream file;
		file.open(s1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix1);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2);
		float max[3] = {0,0,0};
		float min[3] = {0,0,0};
		if (file.is_open()) {
			//std::cout << " here1 \n";
			int i = 0;
			while (!file.eof()) {
				file >> buffer;
				if (i == 0) {
					v = buffer[0];
					if (v != 'v') {
						std::cout << "ERROR 1";
						exit(1);
					}
					else {
					}
					i++;
					continue;
				}
				else if (i == 1) {
					nV = atoi(buffer);
					i++;
					continue;
				}
				else if (i == 2) {
					f = buffer[0];

					if (f != 'f') {
						std::cout << "ERROR 2";
						exit(1);
					}
					else {
					}
					i++;
					continue;
				}
				else if (i == 3) {
					nF = atoi(buffer);
					i++;
					continue;
				}

				if (z < nV) {
					if (i == 8) {
						if (buffer[0] != 'v') {
							hasNormal = 1;
						}
					}
					if (hasNormal == 0) {
						if (i % 4 == 0) {
							i++;
							continue;
						}
						if (atof(buffer) > max[k]) {
							max[k] = atof(buffer);
						}
						if (atof(buffer) < min[k]) {
							min[k] = atof(buffer);

						}
						vertices[z][k++] = atof(buffer);
						//std::cout << buffer << " buffer2 \n";
						//std::cout << vertices[z][k-1] << " vertice1 \n";
						if (k == 3) {
							k = 0;
							z++;
						}
					}
					else {
						if (i == 4 || (i - 4) % 7 == 0) {
							i++;
							continue;
						}
						if (k < 3) {
							if (atof(buffer) > max[k]) {
								max[k] = atof(buffer);
								//std::cout << max[k] << " max \n";
							}
							if (atof(buffer) < min[k]) {
								min[k] = atof(buffer);
								//std::cout << min[k] << " min \n";
							}
						}
						vertices[z][k++] = atof(buffer);
						//std::cout << buffer << " buffer2 \n";
						//std::cout << vertices[z][k-1] << " vertice \n";
						//std::cout << i << " i \n";
						if (k == 6) {
							k = 0;
							z++;
						}
					}
				}
				else {
					if (g == 0) {
						g = i;
					}
					//std::cout << i << " iii \n";
					if (i == g || (i - g) % 4 == 0) {
						//std::cout << i << " kkk \n";
						i++;
						continue;
					}
					faces[x][h++] = atoi(buffer);
					//std::cout << atoi(buffer) << " buffer1 \n";
					//std::cout << buffer << " buffer2 \n";
					//std::cout << faces[x][h-1] << " face \n";
					if (h == 3) {
						h = 0;
						x++;

					}

				}

				i++;
			}
			for (int i = 0; i < nV; i++) {
				for (int j = 0; j < 3; j++) {
					originalV[i][j] = vertices[i][j];
				}
			}
			float mid[3] = { 0,0,0 };
			float finalMax = 0;
			float finalMin = 0;
			for (int i = 0; i < 3; i++) {
				mid[i] = (max[i] + min[i]) / 2;
			}
			//glMatrixMode(GL_MODELVIEW);
			for (int i = 0; i < nV; i++) {
				vertices[i][0] = vertices[i][0] - mid[0];
				if (i == 0) {
					finalMax = vertices[i][0];
					finalMin = vertices[i][0];
				}
				if (finalMax < vertices[i][0]) {
					finalMax = vertices[i][0];
				}
				if (finalMin > vertices[i][0]) {
					finalMin = vertices[i][0];
				}
				vertices[i][1] = vertices[i][1] - mid[1];
				if (finalMax < vertices[i][1]) {
					finalMax = vertices[i][1];
				}
				if (finalMin > vertices[i][1]) {
					finalMin = vertices[i][1];
				}
				vertices[i][2] = vertices[i][2] - mid[2];
				if (finalMax < vertices[i][2]) {
					finalMax = vertices[i][2];
				}
				if (finalMin > vertices[i][2]) {
					finalMin = vertices[i][2];
				}
			}
			if (finalMax > -finalMin) {
				for (int i = 0; i < nV; i++) {
					for (int j = 0; j < 3; j++) {
						vertices[i][j] = vertices[i][j] / finalMax;
					}
				}
			}
			else {
				for (int i = 0; i < nV; i++) {
					for (int j = 0; j < 3; j++) {
						vertices[i][j] = vertices[i][j] / -finalMin;
					}
				}
			}
			//std::cout << finalMax << " max\n";
		}

	}
	if (menu == 2) {
		glutCreateMenu(menu_callback2);
		glutAddMenuEntry("-90", 0);
		glutAddMenuEntry("-45", 1);
		glutAddMenuEntry("-15", 2);
		glutAddMenuEntry("-5", 3);
		glutAddMenuEntry("0", 4);
		glutAddMenuEntry("5", 5);
		glutAddMenuEntry("15", 6);
		glutAddMenuEntry("45", 7);
		glutAddMenuEntry("90", 8);
		glutAttachMenu(GLUT_LEFT_BUTTON);
	}
	if (menu == 3) {
		glutCreateMenu(menu_callback3);
		glutAddMenuEntry("-90", 0);
		glutAddMenuEntry("-45", 1);
		glutAddMenuEntry("-15", 2);
		glutAddMenuEntry("-5", 3);
		glutAddMenuEntry("0", 4);
		glutAddMenuEntry("5", 5);
		glutAddMenuEntry("15", 6);
		glutAddMenuEntry("45", 7);
		glutAddMenuEntry("90", 8);
		glutAttachMenu(GLUT_LEFT_BUTTON);
	}
	if (menu == 4) {
		glutCreateMenu(menu_callback4);
		glutAddMenuEntry("-90", 0);
		glutAddMenuEntry("-45", 1);
		glutAddMenuEntry("-15", 2);
		glutAddMenuEntry("-5", 3);
		glutAddMenuEntry("0", 4);
		glutAddMenuEntry("5", 5);
		glutAddMenuEntry("15", 6);
		glutAddMenuEntry("45", 7);
		glutAddMenuEntry("90", 8);
		glutAttachMenu(GLUT_LEFT_BUTTON);
	}
	if (menu == 5) {
		glutMouseFunc(mouse);
		//glutPostRedisplay();
	}

}
int main(int argc, char** argv)
{


	// window initialization
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(30, 30);

	// create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("ply graph");

	// set empty display function
	glutDisplayFunc(display);


	// create menu
	glutCreateMenu(menu_callback);
	glutAddMenuEntry("reset", 0);
	glutAddMenuEntry("read file", 1);
	glutAddMenuEntry("rotate x", 2);
	glutAddMenuEntry("rotate y", 3);
	glutAddMenuEntry("rotate z", 4);
	glutAddMenuEntry("scale", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	// start glut loop
	glutMainLoop();

	return 0;
}

