#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

int x1Pos = 100, y1Pos = 100;
int x2Pos = 500, y2Pos = 400;

void drawBresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, p, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    p = 2 * dy - dx;

    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(3.0f);

    glBegin(GL_POINTS);

    while (x <= x2)
    {
        glVertex2i(x, y);

        if (p < 0)
        {
            p = p + 2 * dy;
        }
        else
        {
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }

        x = x + 1;
    }

    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBresenhamLine(x1Pos, y1Pos, x2Pos, y2Pos);

    /* Start point */
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2i(x1Pos, y1Pos);
    glEnd();

    /* End point */
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2i(x2Pos, y2Pos);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Bresenham Line Algorithm");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}