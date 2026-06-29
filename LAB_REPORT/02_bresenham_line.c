#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

int x1Pos = 100, y1Pos = 100;
int x2Pos = 600, y2Pos = 350;

void plot(int x, int y) {
    glVertex2i(x, y);
}

void drawBresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;
    int x = x1, y = y1;

    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);

    if (dy <= dx) {
        /* Slope between -1 and 1: step along x */
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            plot(x, y);
            if (p >= 0) {
                y += sy;
                p += 2 * dy - 2 * dx;
            } else {
                p += 2 * dy;
            }
            x += sx;
        }
    } else {
        /* Steep slope: step along y */
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            plot(x, y);
            if (p >= 0) {
                x += sx;
                p += 2 * dx - 2 * dy;
            } else {
                p += 2 * dx;
            }
            y += sy;
        }
    }

    glEnd();
    glFlush();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBresenhamLine(x1Pos, y1Pos, x2Pos, y2Pos);

    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2i(x1Pos, y1Pos);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2i(x2Pos, y2Pos);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
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
