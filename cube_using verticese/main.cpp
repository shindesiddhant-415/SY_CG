#include <GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Light setup
    GLfloat lightPos[] = {2.0f, 2.0f, 3.0f, 1.0f};
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white background
}

void drawCube() {
    float s = 0.5f; // cube size (centered around origin)

    glBegin(GL_TRIANGLES);

    // FRONT (Bright Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-s, -s, s); glVertex3f(s, -s, s); glVertex3f(s, s, s);
    glVertex3f(-s, -s, s); glVertex3f(s, s, s); glVertex3f(-s, s, s);

    // BACK (Bright Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-s, -s, -s); glVertex3f(-s, s, -s); glVertex3f(s, s, -s);
    glVertex3f(-s, -s, -s); glVertex3f(s, s, -s); glVertex3f(s, -s, -s);

    // TOP (Bright Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-s, s, -s); glVertex3f(-s, s, s); glVertex3f(s, s, s);
    glVertex3f(-s, s, -s); glVertex3f(s, s, s); glVertex3f(s, s, -s);

    // BOTTOM (Bright Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-s, -s, -s); glVertex3f(s, -s, -s); glVertex3f(s, -s, s);
    glVertex3f(-s, -s, -s); glVertex3f(s, -s, s); glVertex3f(-s, -s, s);

    // RIGHT (Bright Cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(s, -s, -s); glVertex3f(s, s, -s); glVertex3f(s, s, s);
    glVertex3f(s, -s, -s); glVertex3f(s, s, s); glVertex3f(s, -s, s);

    // LEFT (Bright Magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-s, -s, -s); glVertex3f(-s, -s, s); glVertex3f(-s, s, s);
    glVertex3f(-s, -s, -s); glVertex3f(-s, s, s); glVertex3f(-s, s, -s);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera view: back a bit to see the cube fully
    gluLookAt(1.5, 1.5, 3.0,  // eye position
              0.0, 0.0, 0.0,  // look at origin
              0.0, 1.0, 0.0); // up vector

    drawCube();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Use orthographic projection for perfect proportions
    float size = 1.0f;
    if (aspect >= 1.0f)
        glOrtho(-size * aspect, size * aspect, -size, size, -10.0, 10.0);
    else
        glOrtho(-size, size, -size / aspect, size / aspect, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Perfect Static Bright Cube (Centered at Origin)");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
