#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

#define WIDTH  800
#define HEIGHT 600

int cx = 400, cy = 300;
int rx = 200, ry = 120;

void plotEllipsePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
}

void drawMidpointEllipse(int xc, int yc, int a, int b) {
    float x = 0, y = (float)b;
    float a2 = (float)(a * a);
    float b2 = (float)(b * b);

    /* Region 1: slope > -1 */
    float p1 = b2 - a2 * b + 0.25f * a2;
    float dx = 0, dy = 2 * a2 * y;

    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);

    plotEllipsePoints(xc, yc, (int)x, (int)y);

    while (a2 * (y - 0.5f) > b2 * (x + 1)) {
        x++;
        dx += 2 * b2;
        if (p1 < 0) {
            p1 += dx + b2;
        } else {
            y--;
            dy -= 2 * a2;
            p1 += dx - dy + b2;
        }
        plotEllipsePoints(xc, yc, (int)x, (int)y);
    }

    /* Region 2: slope < -1 */
    float p2 = b2 * (x + 0.5f) * (x + 0.5f) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y > 0) {
        y--;
        dy -= 2 * a2;
        if (p2 > 0) {
            p2 += a2 - dy;
        } else {
            x++;
            dx += 2 * b2;
            p2 += a2 - dy + dx;
        }
        plotEllipsePoints(xc, yc, (int)x, (int)y);
    }

    glEnd();
    glFlush();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMidpointEllipse(cx, cy, rx, ry);

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2i(cx, cy);
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
    glutCreateWindow("Midpoint Ellipse Algorithm");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
} 
