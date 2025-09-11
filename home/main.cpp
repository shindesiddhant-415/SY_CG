#include <windows.h>
#include <GL/glut.h>

void display ()
{

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);//mountains
        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(0.3,0.3);
        glVertex2f(0.55,0.9);
        glVertex2f(0.8,0.3);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//mountains
        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(0.8,0.3);
        glVertex2f(1.05,0.9);
        glVertex2f(1.5,0.3);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//mountains
        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(-0.2,0.3);
        glVertex2f(0.05,0.9);
        glVertex2f(0.3,0.3);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//mountains
        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(-1.2,0.3);
        glVertex2f(-0.95,0.9);
        glVertex2f(-0.7,0.3);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//mountains
        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(-0.7,0.3);
        glVertex2f(-0.45,0.9);
        glVertex2f(-0.2,0.3);
    glEnd();
    glFlush();
        glBegin(GL_QUADS);//wall
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.1,0.0);
        glVertex2f(0.1,0.4);
        glVertex2f(0.4,0.4);
        glVertex2f(0.4,0.0);
    glEnd();
    glFlush();

        glBegin(GL_TRIANGLES);//roof
        glColor3f(0.6f, 0.3f, 0.0f);

        glVertex2f(0.1,0.4);
        glVertex2f(0.25,0.7);
        glVertex2f(0.4,0.4);
    glEnd();
    glFlush();

        glBegin(GL_QUADS);//door
        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex2f(0.2,0.0);
        glVertex2f(0.2,0.15);
        glVertex2f(0.3,0.15);
        glVertex2f(0.3,0.0);
    glEnd();
    glFlush();

        glBegin(GL_QUADS);//windows
        glColor3f(0.0f,1.0f,1.0f);
        glVertex2f(0.15,0.25);
        glVertex2f(0.15,0.3);
        glVertex2f(0.2,0.3);
        glVertex2f(0.2,0.25);
    glEnd();
    glFlush();
        glBegin(GL_QUADS);//windows
        glColor3f(0.0f,1.0f,1.0f);
        glVertex2f(0.3,0.25);
        glVertex2f(0.3,0.3);
        glVertex2f(0.35,0.3);
        glVertex2f(0.35,0.25);
    glEnd();
    glFlush();
    glBegin(GL_QUADS);//tree trumb
        glColor3f(0.5f,0.2f,0.0f);
        glVertex2f(-0.1,0.0);
        glVertex2f(-0.1,0.3);
        glVertex2f(0.0,0.3);
        glVertex2f(0.0,0.0);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//tree branch
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2f(-0.15,0.3);
        glVertex2f(-0.05,0.5);
        glVertex2f(0.05,0.3);
    glEnd();
    glFlush();
    glBegin(GL_QUADS);//tree trumb
        glColor3f(0.5f,0.2f,0.0f);
        glVertex2f(0.5,0.0);
        glVertex2f(0.5,0.3);
        glVertex2f(0.6,0.3);
        glVertex2f(0.6,0.0);
    glEnd();
    glFlush();
        glBegin(GL_TRIANGLES);//tree branch
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2f(0.45,0.3);
        glVertex2f(0.55,0.5);
        glVertex2f(0.65,0.3);
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

