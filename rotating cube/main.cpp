#include <GL/glut.h>

// Rotation angles
float angleX = 0.0f;
float angleY = 0.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background for contrast
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    glBegin(GL_TRIANGLES);

    // Bright colors for each face

    // Front face (bright red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1, -1, 1); glVertex3f(1, -1, 1); glVertex3f(1, 1, 1);
    glVertex3f(-1, -1, 1); glVertex3f(1, 1, 1); glVertex3f(-1, 1, 1);

    // Back face (bright green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1, -1, -1); glVertex3f(-1, 1, -1); glVertex3f(1, 1, -1);
    glVertex3f(-1, -1, -1); glVertex3f(1, 1, -1); glVertex3f(1, -1, -1);

    // Top face (bright blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1, 1, -1); glVertex3f(-1, 1, 1); glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, -1); glVertex3f(1, 1, 1); glVertex3f(1, 1, -1);

    // Bottom face (bright yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1, -1, -1); glVertex3f(1, -1, -1); glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, -1); glVertex3f(1, -1, 1); glVertex3f(-1, -1, 1);

    // Right face (bright cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1, -1, -1); glVertex3f(1, 1, -1); glVertex3f(1, 1, 1);
    glVertex3f(1, -1, -1); glVertex3f(1, 1, 1); glVertex3f(1, -1, 1);

    // Left face (bright magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1, -1, -1); glVertex3f(-1, -1, 1); glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, -1); glVertex3f(-1, 1, 1); glVertex3f(-1, 1, -1);

    glEnd();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    angleX += 1.0f;
    angleY += 1.5f;
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;

    glutPostRedisplay(); // Request redraw
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Bright Cube");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); // Start animation
    glutMainLoop();
    return 0;
}
