#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

/* A regular hexagon defined as a polygon */
float polyX[6] = { 500, 600, 600, 500, 400, 400 };
float polyY[6] = { 200, 260, 380, 440, 380, 260 };

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) glVertex2f(polyX[i], polyY[i]);
    glEnd();

    /* Outline for clarity */
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 6; i++) glVertex2f(polyX[i], polyY[i]);
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
    glutCreateWindow("Draw a Polygon");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
