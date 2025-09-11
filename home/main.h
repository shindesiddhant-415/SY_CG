#include <windows.h>
#include <GL/glut.h>

void display (){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(0.1,0.0);
        glVertex2f(0.1,0.4);
        glVertex2f(0.4,0.4);
        glVertex2f(0.4,0.0);
    glEnd();
}
int main(int argc, char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(300,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OPEN GL PRACTICE SHAPES");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
