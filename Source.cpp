#include <windows.h>

#include "glut.h "

const int width = 768;

const int height = 768;

const int zoom = height / 20;

const int minX = -12, maxX = 12, minY = -12, maxY = 12;

struct colors //Структура цвета

{

	double r, g, b, a;

	void setThis() const

	{

		const colors& color = *this;

		glColor4d(color.r, color.g, color.b, color.a);

	}

};

const color black = { 0, 0, 0, 1 };

const color pink = { 1, 0, 0.5, 1 };

const color grey = { 0.2, 0.2, 0.2, 0.5 };

void draw_fat_pixel(int x, int y, COLOR color)

{

	color.setThis();

	glBegin(GL_POLYGON);

	glVertex2d(x, y);

	glVertex2d(x + 1.0, y);

	glVertex2d(x + 1.0, y + 1.0);

	glVertex2d(x, y + 1.0);

	glEnd();

}

void coords()

{

	for (int i = -width; i < width; i++)

	{

		glLineWidth(0.5);

		glColor3f(0, 0, 0);

		glBegin(GL_LINE_STRIP);

		glVertex2f(-height, i);

		glVertex2f(height, i);

		glEnd();

	}

	for (int i = -width; i < width; i++)

	{

		glLineWidth(0.5);

		glColor3f(0, 0, 0);

		glBegin(GL_LINE_STRIP);

		glVertex2f(i, -height);

		glVertex2f(i, height);

		glEnd();

	}

}

void drawBR(int x1, int x2, int y1, int y2) {//Рисование отсечения

	int px, py, error, lasty = -100;

	int x, y, deltaerr;

	x = x1;

	y = y1;

	px = abs(x2 - x1);

	py = abs(y2 - y1);

	error = 0;

	if (px >= py) deltaerr = py;

	else deltaerr = px;

	while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2)) && ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2)))

	{

		Sleep(50);

		if (x >= minX && x <= maxX && y >= minY && y <= maxY)

		{

			draw_fat_pixel(x, y, grey);

		}

		else

		{

			draw_fat_pixel(x, y, pink);

		}

		glFlush();

		error = error + deltaerr;

		if (px >= py) {

			if (2 * error >= deltaerr) {

				if (y2 < y1) {

					y--;

				}

				else y++;

				error = error - px;

			}

			if (x2 > x1) x++;

			else if (x2 < x1) x--;

		}

		else {

			if (2 * error >= deltaerr) {

				if (x2 > x1) x++;

				else if (x2 < x1) x--;

				error = error - py;

			}

			if (y2 > y1) y++;

			else if (y2 < y1) y--;

		}

	}

}

void figura() //Отрисовка фигуры

{

	int x = minX, y = minY;

	while (x < maxX)

	{

		draw_fat_pixel(x, y, grey);

		x++;

	}

	x = maxX; y = minY;

	while (y < maxY)

	{

		draw_fat_pixel(x, y, grey);

		y++;

	}

	x = maxX; y = maxY;

	while (x > minX)

	{

		draw_fat_pixel(x, y, grey);

		x--;

	}

	y = maxY; x = minX;

	while (y > minY)

	{

		draw_fat_pixel(x, y, grey);

		y--;

	}

	glFlush();

}

void Draw()// функция зарисовки

{

	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// сглаживание

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);

	glEnable(GL_LINE_SMOOTH);

	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	COORDS();

	FIGURA();

	int X1, Y1, X2, Y2, X3, Y3, X4, Y4;

	X1 = -20, Y1 = 0, X2 = 0, Y2 = 20, X3 = 16, Y3 = -5, X4 = -2, Y4 = -15;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X4, Y3, Y4);

	drawBR(X4, X1, Y4, Y1);

	X1 = -10, Y1 = 0, X2 = 0, Y2 = -10, X3 = 10, Y3 = 0, X4 = 0, Y4 = 10;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X4, Y3, Y4);

	drawBR(X4, X1, Y4, Y1);

	X1 = 0, Y1 = 35, X2 = -30, Y2 = -20, X3 = 35, Y3 = -25;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X1, Y3, Y1);

	glFlush();

	glutSwapBuffers();

}

void change(int width, int height) // функция изменения матриц

{

	// размеры области отображения

	glViewport(0, 0, width, height);

	// ортографическая проекция

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// масштабирование

	glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}

int main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// создание окна

	glutInitWindowSize(900, 900);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("Graph");

	//установка основного цвета

	glClearColor(1, 1, 1, 1);

	// вызов ф-и изменения матриц

	change(width, height);

	// вызов ф-и зарисовки

	glutDisplayFunc(Draw);

	// основный цикл

	glutMainLoop();

}