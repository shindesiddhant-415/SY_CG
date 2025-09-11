
#include <GL/glut.h>
#include <stdio.h>

// Global variables for line coordinates
int x1, y1, x2, y2;

// Initialization function
void myInit() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glClear(GL_COLOR_BUFFER_BIT);    // Clear the color buffer
    glMatrixMode(GL_PROJECTION);     // Set projection mode
    glLoadIdentity();                // Reset the matrix
    gluOrtho2D(0, 500, 0, 500);      // Set coordinate system
    glPointSize(2.0);                // Make points more visible
}

// Function to draw a single pixel
void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham's Line Drawing Algorithm
void draw_line(int x1, int y1, int x2, int y2) {
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    dx = abs(dx);
    dy = abs(dy);
    incx = (x2 > x1) ? 1 : -1;
    incy = (y2 > y1) ? 1 : -1;

    x = x1;
    y = y1;

    if (dx > dy) {
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i <= dx; i++) {
            draw_pixel(x, y);
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else {
                e += inc2;
            }
            x += incx;
        }
    } else {
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i <= dy; i++) {
            draw_pixel(x, y);
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
        }
    }
}

// Display callback function
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear screen
    glColor3f(1.0, 1.0, 1.0);     // Set drawing color to white
    draw_line(x1, y1, x2, y2);    // Draw the line
    glFlush();                    // Render now
}

// Main function
int main(int argc, char **argv) {
    printf("Enter coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}


