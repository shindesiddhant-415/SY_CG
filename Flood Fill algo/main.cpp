#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Window dimensions
const int width = 500, height = 500;

// ─────────────────────────────────────────────
// Set a pixel at (x, y)
void setpixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// ─────────────────────────────────────────────
// Get pixel color at (x, y)
void getpixel(int x, int y, GLubyte* color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}

// ─────────────────────────────────────────────
// Compare colors with tolerance
bool isSameColor(GLubyte* c1, GLubyte* c2, int tolerance = 5) {
    return std::abs(c1[0] - c2[0]) < tolerance &&
           std::abs(c1[1] - c2[1]) < tolerance &&
           std::abs(c1[2] - c2[2]) < tolerance;
}

// ─────────────────────────────────────────────
// Flood fill (4-connected)
void floodFill(int x, int y, GLubyte* oldColor, GLubyte* fillColor) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;

    GLubyte current[3];
    getpixel(x, y, current);

    if (isSameColor(current, oldColor)) {
        glColor3ub(fillColor[0], fillColor[1], fillColor[2]);
        setpixel(x, y);

        floodFill(x + 1, y, oldColor, fillColor);
        floodFill(x - 1, y, oldColor, fillColor);
        floodFill(x, y + 1, oldColor, fillColor);
        floodFill(x, y - 1, oldColor, fillColor);
    }
}

// ─────────────────────────────────────────────
// Draw filled triangle in red with black boundary
void draw_polygon() {
    glColor3ub(255, 0, 0); // Red fill
    glBegin(GL_TRIANGLES);
    glVertex2i(250, 400);
    glVertex2i(100, 200);
    glVertex2i(400, 200);
    glEnd();

    glColor3ub(0, 0, 0); // Black border
    glBegin(GL_LINE_LOOP);
    glVertex2i(250, 400);
    glVertex2i(100, 200);
    glVertex2i(400, 200);
    glEnd();

    glFlush();
    glFinish(); // Ensure rendering is complete
}

// ─────────────────────────────────────────────
// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_polygon();

    GLubyte oldColor[3];
    getpixel(250, 300, oldColor); // Sample point inside triangle

    GLubyte fillColor[3] = {0, 255, 0}; // Green fill
    floodFill(250, 300, oldColor, fillColor);
}

// ─────────────────────────────────────────────
// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Reset matrix
    gluOrtho2D(0, width, 0, height);
    glPointSize(1.0); // Set pixel size
}

// ─────────────────────────────────────────────
// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
