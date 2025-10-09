#include <GL/glut.h>

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
    glReadPixels(x, height - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}

// ─────────────────────────────────────────────
// Read pixel color and return pointer
GLubyte* readpixel(int x, int y) {
    static GLubyte pixel[3];
    glReadPixels(x, height - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    return pixel;
}

// ─────────────────────────────────────────────
// Draw filled triangle in red with black boundary
void draw_polygon() {
    // Fill triangle in red
    glColor3ub(255, 0, 0); // Red
    glBegin(GL_TRIANGLES);
   glVertex2i(250, 400); // Top vertex
    glVertex2i(100, 200); // Bottom left
    glVertex2i(400, 200); // Bottom right

    glEnd();

    // Draw triangle boundary in black
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_LINE_LOOP);
    glVertex2i(250, 400); // Top vertex
    glVertex2i(100, 200); // Bottom left
    glVertex2i(400, 200); // Bottom right

    glEnd();

    glFlush();
}

// ─────────────────────────────────────────────
// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_polygon(); // Draw red triangle with black border
}

// ─────────────────────────────────────────────
// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width, 0, height);
}

// ─────────────────────────────────────────────
// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Red Triangle with Black Border");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
