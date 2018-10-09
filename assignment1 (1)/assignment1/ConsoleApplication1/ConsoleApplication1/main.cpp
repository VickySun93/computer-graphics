#include "GL/glut.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <cstring>
const int width = 800;
const int height = 600;
int nvertex;
int nface;
int normal = 0;
float vertices[1024][6];
int faces[1024][3];
float maxx;
float minx;
float maxy;
float miny;
float maxz;
float minz;
float longdis[3];
float longdis2;
float light_diffuse[] = { 1.0, 0.9, 0.58, 1.0 };
float light_position[] = { 1.0, 1.0, -1.0, 0.0 };
float center[3];
float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
float mat_shininess[] = { 50.0 };
float statematrix[16];
float originalmatrix[16];

void mkLighting(void) {
	glShadeModel(GL_SMOOTH);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
static void init() {
	// set clear color to 20% gray
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	        //float s = width / 2.0;
	         //if (height < width) s = height / 2;
	         //glOrtho(-s, s, -s, s, 1, 100);
	//glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1, 50);
	mkLighting();
}
static void display() { 
	     //glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(1.f, 0.f, 0.f);
	       //glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	//glColor3f(1.f, 0.f, 0.f);
	   /*glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1, 50);
	    mkLighting();*/
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(statematrix);
	//gluLookAt();
	//center[0] = -center[0];
	//center[1] = -center[1];
	//center[2] = -center[2];
	//printf("c=%f,c=%f,c=%f",center[0],center[1],center[2]);
	//glTranslatef(center[0],center[1],center[2]);
	//glTranslatef(10.0f, 10.0f, 10.0f);
	//glScalef(2.0f / longdis2, 2.0f / longdis2, 2.0f / longdis2);
	
	//glScalef(1.0f / 1000, 1.0f / 1000,1.0f / 1000);
	//printf("longdis222222========%f\n", longdis2);

	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < nface; i++) {
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(vertices[faces[i][0]-1][0], vertices[faces[i][0]-1][1], vertices[faces[i][0]-1][2]);
		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(vertices[faces[i][1]-1][0], vertices[faces[i][1]-1][1], vertices[faces[i][1]-1][2]);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(vertices[faces[i][2]-1][0], vertices[faces[i][2]-1][1], vertices[faces[i][2]-1][2]);
		//printf("vertices1=%f,vertices2=%f,vertices3=%f", vertices[faces[i][0] - 1][0], vertices[faces[i][0] - 1][1], vertices[faces[i][0] - 1][2]);
	}
	glEnd();
	//printf("vertices[2][0]=%f,vertices[2][1]=%f,vertices[2][2]=%f", vertices[2][0], vertices[2][1], vertices[2][2]);
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) { /* call back for reshaping        */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1, 50);
	if (w <= h) {
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	}
	else {
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	}
	
}


using namespace std;

//split string
int  split1(char* line) {
	char *point;
	int count;
	point = strtok(line, " ");
	if (strcmp(point, "v")!=0){
		cout << "notply";
		return 1;
	}
	point = strtok(NULL, " ");
	//printf("point=%s\n", point);
	nvertex = atof(point);
	printf("nvertex=%d\n", nvertex);
	count = 2;
	while (point != NULL) {
		//cout << point << endl;
		point = strtok(NULL, " ");
		//
		count++;
		if (count > 3) {
			cout << "count>3\n";
			return 1;
		}
	}
	//printf("count=%d", count);
	return 0;
}
int  split2(char* str) {
	char *point;
	int count;
	point = strtok(str, " ");
	if (strcmp(point, "f") != 0) {
		cout << "notply";
		return 1;
	}
	point = strtok(NULL, " ");
	nface = atof(point);
	printf("nface=%d\n", nface);
	count =2;
	while (point != NULL) {
		//cout << point << endl;
		point = strtok(NULL, " ");
		count++;
		if (count > 3) {
			cout << "count>3\n";
			return 1;
		}
	}
	//printf("count=%d", count);
	return 0;
}
/*float* split3(char* line,int error) {
	char *point;
	int count;
	point = strtok(line, " ");
	if (strcmp(point, "f") != 0&& strcmp(point, "v") != 0) {
		cout << "not ply";
		error = 1;
		return;
	}
	count = 1;
	while (point != NULL) {
		cout << point << endl;
		point = strtok(NULL, " ");
		 //= atof(point);
		printf("nface=%d\n", nface);
		count++;
		
	}
	//printf("count=%d", count);
	return;
}*/


void mouse(int button, int state, int x, int y) {

	if ((button == 3) || (button == 4)) {
		if (button == 3) {
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(statematrix);
			glScalef(1.05f, 1.05f,1.05f );
			glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
			
		}
		else {
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(statematrix);
			glScalef(0.95f, 0.95f, 0.95f);
			glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
			
		}
	}
}
static void menu_callback2(int menu) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(statematrix);
	if (menu == 0) {
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 1) {
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 2) {
		glRotatef(-15.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 3) {
		glRotatef(-5.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 5) {
		glRotatef(5.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 6) {
		glRotatef(15.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 7) {
		glRotatef(45.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 8) {
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
}
static void menu_callback3(int menu) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(statematrix);
	if (menu == 0) {
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 1) {
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 2) {
		glRotatef(-15.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 3) {
		glRotatef(-5.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 5) {
		glRotatef(5.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 6) {
		glRotatef(15.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 7) {
		glRotatef(45.0, 0.0,1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 8) {
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
}
static void menu_callback4(int menu) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(statematrix);
	if (menu == 0) {
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 1) {
		glRotatef(-45.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 2) {
		glRotatef(-15.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 3) {
		glRotatef(-5.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 5) {
		glRotatef(5.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 6) {
		glRotatef(15.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 7) {
		glRotatef(45.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	else if (menu == 8) {
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
}
static void menu_callback(int menu) {
	std::cout << "Menu Item " << menu << " was clicked\n";
	if (menu == 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(originalmatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
	}
	if (menu == 1) {
		

			char filename[100];
			cout << "Please enter file name:";
			cin >> filename;
			cout << filename;
			cout << "\n";
			//getline(cin, input_line);
			//reading from a file
			ifstream infile(filename);
			if (infile.is_open()) {
				string a;
				getline(infile, a);
				char *line1= new char[a.length() + 1];;		
				strcpy(line1, a.c_str());
				printf("line1 = %s\n", line1);
				if (split1(line1) == 1) {
					cout << "notply";
					return;
				}
				string b;
				getline(infile, b);
				char *line2 = new char[b.length() + 1];;
				strcpy(line2, b.c_str());
				if (split2(line2) == 1) {
					cout << "notply";
					return;
				}
				string c;
				
				//vertices = new float*;
				//faces = new int*;
				getline(infile, c);
					//cout << c << '\n';
				char *line3 = new char[c.length()+1];
				strcpy(line3, c.c_str());
				char *point;
				point = strtok(line3, " ");
				int count2 = 1;
				float thirdline[6];
				int i = 0;
				while (point != NULL) {
					//cout << point << endl;
					point = strtok(NULL, " ");
					if (point != NULL) {
						thirdline[i++] = atof(point);
					}
					count2++;
					if (count2 > 8) {
						cout << "notplyfile2";
						return;
					}
				}
				printf("count2=%d\n", count2);
				
				if (count2 == 8) {
					normal = 1;
					//float **vertices = (float**)malloc(sizeof(float*) * 6);
					//int **faces = (int**)malloc(sizeof(int*) * 3);
					int countvertex = 0;
					for (int i = 0; i < 6; i++) {
						vertices[countvertex][i] = thirdline[i];
					}
					maxx = vertices[countvertex][0];
					minx = vertices[countvertex][0];
					maxy = vertices[countvertex][1];
					miny = vertices[countvertex][1];
					maxz = vertices[countvertex][2];
					minz = vertices[countvertex][2];
					countvertex++;
					while (countvertex < nvertex) {
						getline(infile, c);
						char *line3 = new char[c.length() + 1];
						strcpy(line3, c.c_str());
						char *point;
						point = strtok(line3, " ");
						float vertex1[6];
						int i = 0;
						while (point != NULL) {
							point = strtok(NULL, " ");
							if (point != NULL) {
								vertex1[i++] = atof(point);
							}
						}
						for (int i = 0; i < 6; i++) {
							vertices[countvertex][i] = vertex1[i];
						}
						if (vertices[countvertex][0] > maxx)maxx = vertices[countvertex][0];
						if (vertices[countvertex][0] < minx)minx = vertices[countvertex][0];
						if (vertices[countvertex][1] > maxy)maxy = vertices[countvertex][1];
						if (vertices[countvertex][1] < miny)miny = vertices[countvertex][1];
						if (vertices[countvertex][2] > maxz)maxz = vertices[countvertex][2];
						if (vertices[countvertex][2] < minz)minz = vertices[countvertex][2];
						countvertex++;
						//vertices[countvertex++] = vertex1;
					}
					int countface = 0;
					while (countface < nface) {
						getline(infile, c);
						char *line3 = new char[c.length() + 1];
						strcpy(line3, c.c_str());
						char *point;
						point = strtok(line3, " ");
						int face[3];
						int i = 0;
						while (point != NULL) {
							point = strtok(NULL, " ");
							if (point != NULL) {
								face[i++] = atoi(point);
							}
						}
						for (int i = 0; i < 3; i++) {
							faces[countface][i] = face[i];
						}
						countface++;
						//faces[countface++] = face;
					}
				}else if (count2 ==5) {
					normal = 0;
					//float **vertices = (float**)malloc(sizeof(float*) * 3);
					//int **faces = (int**)malloc(sizeof(int*) * 3);
					int countvertex = 0;
					/*float thirdline2[3];
					thirdline2[0] = thirdline[0];
					thirdline2[1] = thirdline[1];
					thirdline2[2] = thirdline[2];
					printf("here1");
					vertices[countvertex++] = thirdline2;*/
					for (int i = 0; i < 3; i++) {
						vertices[countvertex][i] = thirdline[i];
					}
					maxx = vertices[countvertex][0];
					minx = vertices[countvertex][0];
					maxy = vertices[countvertex][1];
					miny = vertices[countvertex][1];
					maxz = vertices[countvertex][2];
					minz = vertices[countvertex][2];
					countvertex++;
					while (countvertex < nvertex) {
						getline(infile, c);
						char *line3 = new char[c.length() + 1];
						strcpy(line3, c.c_str());
						char *point;
						point = strtok(line3, " ");
						float vertex1[3];
						int i = 0;
						//printf("here2");
						while (point != NULL) {
							point = strtok(NULL, " ");
							if (point != NULL) {
								vertex1[i++] = atof(point);
							}
						}
						//printf("here3");
						//printf("v %f %f %f\n", vertex1[0], vertex1[1], vertex1[2]);
						//vertices[countvertex++] = vertex1;
						for (int i = 0; i < 3; i++) {
							vertices[countvertex][i] = vertex1[i];
						}
						if (vertices[countvertex][0] > maxx)maxx = vertices[countvertex][0];
						if (vertices[countvertex][0] < minx)minx = vertices[countvertex][0];
						if (vertices[countvertex][1] > maxy)maxy = vertices[countvertex][1];
						if (vertices[countvertex][1] < miny)miny = vertices[countvertex][1];
						if (vertices[countvertex][2] > maxz)maxz = vertices[countvertex][2];
						if (vertices[countvertex][2] < minz)minz = vertices[countvertex][2];
						countvertex++;
					}
					int countface = 0;
					while (countface < nface) {
						getline(infile, c);
						char *line3 = new char[c.length() + 1];
						strcpy(line3, c.c_str());
						char *point;
						point = strtok(line3, " ");
						int face[3];
						int i = 0;
						while (point != NULL) {
							point = strtok(NULL, " ");
							if (point != NULL) {
								face[i++] = atoi(point);
							}
							
						}
						for (int i = 0; i < 3; i++) {
							faces[countface][i] = face[i];
						}
						countface++;
						//faces[countface++] = face;
					}
					//printf("here4");
					for (int i = 0; i < nvertex; i++) {
						printf("v %f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
					}
					for (int i = 0; i < nface; i++) {
						printf("f %d %d %d\n", faces[i][0], faces[i][1], faces[i][2]);
					}

				}
				//printf("x1%f,x2%f,y1%f,y2%f,z1%f,z2%f", maxx, minx, maxy, miny, maxz, minz);
				longdis[0] = maxx - minx;
				longdis[1] = maxy - miny;
				longdis[2] = maxz - minz;
			//	printf("long%f,long%f,long%f", longdis[0], longdis[1], longdis[2]);

				center[0] = (maxx + minx) / 2;
				center[1] = (maxy + miny) / 2;
				center[2] = (maxz + minz) / 2;
				//printf("center[0]=%f,center[1]=%f,center[2]=%f", center[0], center[1], center[2]);
				if (longdis[0] > longdis[1]) {
					if (longdis[0] > longdis[2]) {
						longdis2 = longdis[0];
					}
					else {
						longdis2 = longdis[2];
					}
				}else {
					if (longdis[1] > longdis[2]) {
						longdis2 = longdis[1];
					}
					else {
						longdis2 = longdis[2];
					}

				}
				glMatrixMode(GL_PROJECTION);
				//float s = width / 2.0;
				//if (height < width) s = height / 2;
				//glOrtho(-s, s, -s, s, 1, 100);
				//glOrtho(-100, 100, -100, 100, -2, 2);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glScalef(1.0f / longdis2, 1.0f / longdis2, 1.0f / longdis2);
				glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
				glGetFloatv(GL_MODELVIEW_MATRIX, originalmatrix);
			
				//printf("c=%f,c=%f,c=%f",center[0],center[1],center[2]);
				//glTranslatef(-center[0],-center[1],-center[2]);
				
				//printf("longdis2=%f", longdis2);
				
				//glGetFloatv(GL_MODELVIEW_MATRIX, statematrix);
				infile.close();
			}
			else {
				cout << "Unable to open the file";
			}
			//cout << "Reading from the file" << endl;
			
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
	glutCreateWindow("Example 3: Menu Creation");

	//init();
	// set empty display function
	glutDisplayFunc(display);
	//(reshape);
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