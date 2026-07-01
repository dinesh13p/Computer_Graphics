#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

/* Fixed point of scaling */
float fixX = 300, fixY = 250;

/* Original triangle vertices */
float triX[3] = { 300, 380, 300 };
float triY[3] = { 250, 250, 350 };

float sx = 1.8f, sy = 1.8f; /* scale factors */

void scalePoint(float x, float y, float fx, float fy, float sx, float sy, float *xOut, float *yOut) {
    /* Scale relative to fixed point (fx, fy) */
    *xOut = fx + (x - fx) * sx;
    *yOut = fy + (y - fy) * sy;
}

void drawTriangle(float xs[3], float ys[3]) {
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 3; i++) glVertex2f(xs[i], ys[i]);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawTriangle(triX, triY);

    float newX[3], newY[3];
    for (int i = 0; i < 3; i++) {
        scalePoint(triX[i], triY[i], fixX, fixY, sx, sy, &newX[i], &newY[i]);
    }
    glColor3f(0.0f, 1.0f, 1.0f);
    drawTriangle(newX, newY);

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
    glutCreateWindow("2D Scaling Transformation");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
