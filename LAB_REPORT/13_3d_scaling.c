#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float X[8]={350,400,400,350,350,400,400,350},
      Y[8]={250,250,300,300,250,250,300,300},
      Z[8]={0,0,0,0,50,50,50,50};
int E[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
float s=1.8f;

void cube(int scale){
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        int a=E[i][0],b=E[i][1];
        float f=scale?s:1.0f;
        float ax=X[a]*f, ay=Y[a]*f, az=Z[a]*f;
        float bx=X[b]*f, by=Y[b]*f, bz=Z[b]*f;
        glVertex2f(ax+0.5f*az, ay+0.5f*az);
        glVertex2f(bx+0.5f*bz, by+0.5f*bz);
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
    glutCreateWindow("3D Scaling Transformation");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}