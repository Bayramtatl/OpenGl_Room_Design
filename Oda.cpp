#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>
GLsizei ekranGenisligi = 700, ekranYuksekligi = 650;    // Initial display window size.
GLint xRaster, yRaster = 180;          // Initialize raster position. 25 180

GLubyte label[39] = { 'T', 'U', 'R',   'I', 'R', 'L',   'I', 'R', 'A',
'E', 'N', 'G',   'R', 'U', 'S',   'F', 'A', 'S',
'Z', 'E', 'L',   'S', 'I', 'L',   'M', 'I', 'S',
'P', 'O', 'L',   'J', 'A', 'P',   'A', 'R', 'A',   'G','A','F' };

GLfloat veriler[13] = { 10.4, 7.2, 6.5, 5.0, 4.5, 4.0,
3.9, 3.9, 3.3, 3.3, 3.2, 3.0, 2.7 };
GLfloat renkler[13][4] = { {1.0f, 0.0f, 0.0f, 0.0f},{1.0f, 1.0f, 0.0f, 0.0f},{1.0f, 0.0f, 1.0f, 0.0f},{0.0f, 1.0f, 1.0f, 1.0f},
	{1.0f, 0.5f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f,0.0f}, {0.0f, 0.0f, 1.0f,0.0f}, {0.5f, 1.0f, 1.0f,0.0f}, {0.5f, 0.5f, 0.5f,0.0f},
	{2.0f, 0.5f, 1.0f, 0.0f},{0.1f, 0.1f, 0.0f, 0.0f},{0.0f, 0.5f, 1.0f, 0.0f},{0.7f,0.3f,0.8f,0.0f} };

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);    // White display window.
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, ekranGenisligi, 0.0, ekranYuksekligi);
}

void barChart(void)
{
	GLint i, k;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);     //  Set bar color to red.
	for (k = 0; k < 13; k++) {
		glColor4f(renkler[k][0], renkler[k][1], renkler[k][2], renkler[k][3]);
		glRecti(20 + k * 50, 140, 40 + k * 50, veriler[k]*55);
	}
	glColor3f(0.0, 0.0, 0.0);           //  Set text color to black.
	xRaster = 20;           //  Display chart labels.
	for (i = 0; i < 13; i++) {
		if (i % 6 == 5) {
			yRaster -= 40;
			xRaster = 20;
		}
		glRasterPos2i(xRaster, yRaster);
		glColor4f(renkler[i][0], renkler[i][1], renkler[i][2], renkler[i][3]);
		glRecti(30 + xRaster, yRaster, 40 + xRaster, yRaster+10);
		for (k = 3 * i; k < 3 * i + 3; k++) {
			glColor3f(0.0, 0.0, 0.0);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
		}
		xRaster += 70;
	}
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(ekranGenisligi, ekranYuksekligi);
	glutCreateWindow("Bar Chart Data Plot");
	init();
	glutDisplayFunc(barChart);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}