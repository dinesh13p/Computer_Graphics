#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float X[8]={450,550,550,450,450,550,550,450},
      Y[8]={250,250,350,350,250,250,350,350},
      Z[8]={0,0,0,0,100,100,100,100};
int E[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};

void cube(int reflect){
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        int a=E[i][0],b=E[i][1];
        float za=reflect?-Z[a]:Z[a], zb=reflect?-Z[b]:Z[b];
        glVertex2f(X[a]+0.5f*za, Y[a]+0.5f*za);
        glVertex2f(X[b]+0.5f*zb, Y[b]+0.5f*zb);
    }
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,0); cube(0);
    glColor3f(0,1,1); cube(1);
    glFlush();
}

void keyboard(unsigned char key,int x,int y){ if(key==27) exit(0); }

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("3D Reflection Transformation");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}