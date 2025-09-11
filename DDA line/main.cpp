#include <iostream>
#include <GL/glut.h>
using namespace std;

int x1, y1, x2, y2;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 > x1) ? 1 : -1;
    int sy = (y2 > y1) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        drawPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Red color
    drawLine(x1, y1, x2, y2);
    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1); // White background
    glColor3f(0, 0, 0);       // Black drawing color
    glPointSize(3);           // Bigger dots
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    cout << "Enter starting point (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter ending point (x2 y2): ";
    cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
