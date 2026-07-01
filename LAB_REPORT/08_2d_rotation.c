#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

#define WIDTH  800
#define HEIGHT 600
#define PI 3.14159265358979323846

/* Original triangle vertices (about pivot point) */
float pivotX = 400, pivotY = 300;
float triX[3] = { 400, 500, 400 };
float triY[3] = { 300, 300, 420 };

float angleDeg = 60.0f; /* rotation angle in degrees */

void rotatePoint(float x, float y, float px, float py, float angle, float *xOut, float *yOut) {
    float rad = angle * PI / 180.0f;
    float xt = x - px;
    float yt = y - py;
    *xOut = xt * cos(rad) - yt * sin(rad) + px;
    *yOut = xt * sin(rad) + yt * cos(rad) + py;
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
        rotatePoint(triX[i], triY[i], pivotX, pivotY, angleDeg, &newX[i], &newY[i]);
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
    glutCreateWindow("2D Rotation Transformation");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
