#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float X[8]={100,200,200,100,100,200,200,100},
      Y[8]={150,150,250,250,150,150,250,250},
      Z[8]={0,0,0,0,100,100,100,100};
int E[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
float tx=250,ty=100,tz=0;

void cube(float dx,float dy,float dz){
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        int a=E[i][0],b=E[i][1];
        glVertex2f(X[a]+dx+0.5f*(Z[a]+dz), Y[a]+dy+0.5f*(Z[a]+dz));
        glVertex2f(X[b]+dx+0.5f*(Z[b]+dz), Y[b]+dy+0.5f*(Z[b]+dz));
    }
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,0); cube(0,0,0);
    glColor3f(0,1,1); cube(tx,ty,tz);
    glFlush();
}

void keyboard(unsigned char key,int x,int y){ if(key==27) exit(0); }

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("3D Translation Transformation");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}