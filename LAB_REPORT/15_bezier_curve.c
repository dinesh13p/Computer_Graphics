#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float cx[4]={100,250,550,700}, cy[4]={150,450,100,400};

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.4f,0.4f,0.4f);
    glBegin(GL_LINE_STRIP);
        for(int i=0;i<4;i++) glVertex2f(cx[i],cy[i]);
    glEnd();

    glColor3f(1,0,0);
    glPointSize(7);
    glBegin(GL_POINTS);
        for(int i=0;i<4;i++) glVertex2f(cx[i],cy[i]);
    glEnd();

    glColor3f(1,1,0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<=100;i++){
        float t=i/100.0f, u=1-t;
        float b0=u*u*u, b1=3*t*u*u, b2=3*t*t*u, b3=t*t*t;
        glVertex2f(b0*cx[0]+b1*cx[1]+b2*cx[2]+b3*cx[3],
                   b0*cy[0]+b1*cy[1]+b2*cy[2]+b3*cy[3]);
    }
    glEnd();

    glFlush();
}

void keyboard(unsigned char key,int x,int y){ if(key==27) exit(0); }

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bezier Curve");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}