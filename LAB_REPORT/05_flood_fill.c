#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WIDTH 800
#define HEIGHT 600
/* 0=BLACK 1=WHITE 2=GREEN 3=RED */

int pixels[WIDTH][HEIGHT] = {0};

#define INBOUNDS(x, y) ((x) >= 0 && (x) < WIDTH && (y) >= 0 && (y) < HEIGHT)

void putPixel(int x, int y, int c)
{
    if (INBOUNDS(x, y))
        pixels[x][y] = c;
}
int getPixel(int x, int y) { return INBOUNDS(x, y) ? pixels[x][y] : -1; }

void floodFill(int x, int y, int oldC, int newC, int conn)
{
    static const int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    static const int dy[8] = {0, 0, 1, -1, 1, -1, -1, 1};

    if (getPixel(x, y) != oldC)
        return;
    putPixel(x, y, newC);

    for (int i = 0; i < conn; i++)
        floodFill(x + dx[i], y + dy[i], oldC, newC, conn);
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    for (int x = x1; x <= x2; x++)
    {
        putPixel(x, y1, 1);
        putPixel(x, y2, 1);
    }
    for (int y = y1; y <= y2; y++)
    {
        putPixel(x1, y, 1);
        putPixel(x2, y, 1);
    }
}

void renderPixels()
{
    static const float col[4][3] = {{0, 0, 0}, {1, 1, 1}, {0, 1, 0}, {1, 0, 0}};
    glBegin(GL_POINTS);
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            if (pixels[x][y])
            {
                glColor3fv(col[pixels[x][y]]);
                glVertex2i(x, y);
            }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    renderPixels();
    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);

    drawRectangle(100, 100, 300, 250);
    floodFill(150, 150, 0, 2, 4); /* 4-connected */

    drawRectangle(450, 100, 650, 250);
    floodFill(500, 150, 0, 3, 8); /* 8-connected */
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("4 and 8 Connected Flood Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}