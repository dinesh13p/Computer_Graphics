#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

/* Original triangle vertices */
float triX[3] = { 100, 200, 100 };
float triY[3] = { 100, 100, 250 };

/* Translation factors */
float tx = 250.0f, ty = 150.0f;

void translatePoint(float x, float y, float tx, float ty, float *xOut, float *yOut) {
    /* Homogeneous translation: [x' y' 1] = [x y 1] * T  */
    *xOut = x + tx;
    *yOut = y + ty;
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
        translatePoint(triX[i], triY[i], tx, ty, &newX[i], &newY[i]);
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
    glutCreateWindow("2D Translation Transformation");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
