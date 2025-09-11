#include <GL/glut.h>
#include <cmath>

void plot_point(int xl, int yl, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xl + x, yl + y);
    glVertex2i(xl + x, yl - y);
    glVertex2i(xl - x, yl + y);
    glVertex2i(xl - x, yl - y);
    glVertex2i(xl + y, yl + x);
    glVertex2i(xl + y, yl - x);
    glVertex2i(xl - y, yl + x);
    glVertex2i(xl - y, yl - x);
    glEnd();
}

void bresenham_circle(int xl, int yl, int r)
{
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    plot_point(xl, yl, x, y);

    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p = p + 4 * x + 6;
        }
        else
        {
            y--;
            p = p + 4 * (x - y) + 10;
        }
        plot_point(xl, yl, x, y);
    }
    glFlush();
}

void Draw_circle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int xl = 300, yl = 250, r = 125;
    bresenham_circle(xl, yl, r);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Circle algorithm");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw_circle);
    glutMainLoop();
    return 0;
}
