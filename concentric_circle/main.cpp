#include <GL/glut.h>
#include <cmath>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // white background
    gluOrtho2D(0, 600, 0, 600);
}

// DDA Circle Drawing
void ddacircle(int xc, int yc, int r) {
    float x = 0;
    float y = r;
    float P = 1 - r;

    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        x++;
        if (P < 0)
            P += 2 * x + 1;
        else {
            y--;
            P += 2 * (x - y) + 1;
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 300, yc = 300;      // center of inner circle
    int r_inner = 100;            // radius of inner circle
    int r_outer = 80;              // radius of outer circles

    // Draw the inner (central) circle in red
    glColor3f(0, 1, 0);
    ddacircle(xc, yc, r_inner);

    // Draw 5 outer circles whose centers lie on the inner circle
    glColor3f(0, 0, 0);
    for (int i = 0; i < 5; i++) {
        float angle = i * (2 * 3.14159 / 5); // 360/5 in radians
        int ox = xc + r_inner * cos(angle);
        int oy = yc + r_inner * sin(angle);
        ddacircle(ox, oy, r_outer);
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("5 Circles Around Central Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
