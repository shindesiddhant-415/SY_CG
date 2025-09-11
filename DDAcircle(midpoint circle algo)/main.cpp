#include <GL/glut.h>
#include <iostream>
using namespace std;

int circle_xc, circle_yc, circle_r;

// Function to plot the symmetric points
void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(circle_xc + x, circle_yc + y);
        glVertex2i(circle_xc - x, circle_yc + y);
        glVertex2i(circle_xc + x, circle_yc - y);
        glVertex2i(circle_xc - x, circle_yc - y);
        glVertex2i(circle_xc + y, circle_yc + x);
        glVertex2i(circle_xc - y, circle_yc + x);
        glVertex2i(circle_xc + y, circle_yc - x);
        glVertex2i(circle_xc - y, circle_yc - x);
    glEnd();
    glFlush();
}

// Midpoint Circle Algorithm
void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 1 - r;

    plotPoints(x, y);

    while (x < y) {
        if (d < 0) {
            d = d + 2 * x + 3;
        } else {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        plotPoints(x, y);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);        // Clear the color buffer
    glColor3f(0.0, 1.0, 0.0);            // Set drawing color to white
    midpointCircle(circle_xc, circle_yc, circle_r);  // Draw the circle
    glFlush();
}

// Initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);    // Set background color to black
    gluOrtho2D(0, 600, 0, 600);          // Define the 2D orthographic projection
}

// Main function
int main(int argc, char** argv) {
    std::cout << "Enter circle center (xc yc): ";
    std::cin >> circle_xc >> circle_yc;
    std::cout << "Enter circle radius (r): ";
    std::cin >> circle_r;

    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");

    init();
    glutDisplayFunc(display);                       // Register display callback
    glutMainLoop();
    return 0;
}
