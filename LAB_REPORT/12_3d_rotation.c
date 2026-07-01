#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

float X[8]={350,450,450,350,350,450,450,350},
      Y[8]={250,250,350,350,250,250,350,350},
      Z[8]={0,0,0,0,100,100,100,100};
int E[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
float angleDeg=45;

void cube(int rotate){
    float rad=angleDeg*3.14159265f/180.0f, c=cos(rad), s=sin(rad);
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        int a=E[i][0],b=E[i][1];
        float ax=X[a],ay=Y[a],bx=X[b],by=Y[b];
        if(rotate){
            ax=X[a]*c-Y[a]*s; ay=X[a]*s+Y[a]*c;
            bx=X[b]*c-Y[b]*s; by=X[b]*s+Y[b]*c;
        }
        glVertex2f(ax+0.5f*Z[a], ay+0.5f*Z[a]);
        glVertex2f(bx+0.5f*Z[b], by+0.5f*Z[b]);
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
    glutCreateWindow("3D Rotation Transformation");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}