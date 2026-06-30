#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

float x1Pos = 100.0f, y1Pos = 100.0f;
float x2Pos = 500.0f, y2Pos = 400.0f;

void drawDDALine(float x1p, float y1p, float x2p, float y2p)
{
    float dx = x2p - x1p;
    float dy = y2p - y1p;
    int steps = (int)(fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1p, y = y1p;

    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2i((GLint)(x + 0.5f), (GLint)(y + 0.5f));
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawDDALine(x1Pos, y1Pos, x2Pos, y2Pos);

    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2i((GLint)x1Pos, (GLint)y1Pos);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2i((GLint)x2Pos, (GLint)y2Pos);
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
    glutCreateWindow("DDA Line Algorithm");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
