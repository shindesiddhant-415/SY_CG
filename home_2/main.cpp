#include <windows.h>
#include <GL/glut.h>

void display ()
{

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);//wall
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,0.4);
        glVertex2f(0.3,0.4);
        glVertex2f(0.3,0.0);
    glEnd();
    glFlush();

       glBegin(GL_QUADS);//wall
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.3,0.0);
        glVertex2f(0.3,0.4);
        glVertex2f(0.6,0.6);
        glVertex2f(0.6,0.2);
    glEnd();
    glFlush();

        glBegin(GL_TRIANGLES);//roof
        glColor3f(0.6f, 0.3f, 0.0f);
        glVertex2f(0.0,0.4);
        glVertex2f(0.1,0.6);
        glVertex2f(0.3,0.4);
    glEnd();
    glFlush();

       glBegin(GL_QUADS);//wall
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.3,0.4);
        glVertex2f(0.1,0.6);
        glVertex2f(0.5,0.8);
        glVertex2f(0.6,0.6);
    glEnd();
    glFlush();

        glBegin(GL_QUADS);//door
        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex2f(0.1,0.0);
        glVertex2f(0.1,0.3);
        glVertex2f(0.2,0.3);
        glVertex2f(0.2,0.0);
    glEnd();
    glFlush();

     glBegin(GL_QUADS);//pluse
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.4,-0.2);
        glVertex2f(-0.4,-0.05);
        glVertex2f(-0.35,-0.05);
        glVertex2f(-0.35,-0.2);
    glEnd();
    glFlush();

      glBegin(GL_QUADS);//pluse
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.45,-0.15);
        glVertex2f(-0.45,-0.1);
        glVertex2f(-0.3,-0.1);
        glVertex2f(-0.3,-0.15);
    glEnd();
    glFlush();


    glScalef(2, 2, 2);
    glBegin(GL_LINES);//medical sign
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2d(-0.4,-0.2);
    glVertex2d(-0.4,-0.15);
    glVertex2d(-0.4,-0.15);
    glVertex2d(-0.45,-0.15);
    glVertex2d(-0.45,-0.15);
    glVertex2d(-0.45,-0.1);
    glVertex2d(-0.45,-0.1);
    glVertex2d(-0.4,-0.1);
    glVertex2d(-0.4,-0.1);
    glVertex2d(-0.4,-0.05);
    glVertex2d(-0.35,-0.05);
    glVertex2d(-0.4,-0.05);
    glVertex2d(-0.35,-0.05);
    glVertex2d(-0.35,-0.1);
    glVertex2d(-0.35,-0.1);
    glVertex2d(-0.3,-0.1);
    glVertex2d(-0.3,-0.1);
    glVertex2d(-0.3,-0.15);
    glVertex2d(-0.3,-0.15);
    glVertex2d(-0.35,-0.15);
    glVertex2d(-0.35,-0.15);
    glVertex2d(-0.35,-0.2);
    glVertex2d(-0.35,-0.2);
    glVertex2d(-0.4,-0.2);
    glEnd();
    glFlush();

    glBegin(GL_LINES);//addition
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.4,-0.2);
        glVertex2f(0.4,-0.1);
        glVertex2f(0.35,-0.15);
        glVertex2f(0.45,-0.15);
    glEnd();
    glFlush();







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

