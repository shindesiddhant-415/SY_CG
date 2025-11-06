#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

float xmin = -100, ymin = -100;
float xmax =  100, ymax =  100;

typedef struct points
{
    float x, y;
    int CODE[4];   // [Top, Bottom, Right, Left]
} PT;

PT p1, p2, p3, p4;

// -------------------------------------------------------------

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-600, 600, -600, 600);
    glPointSize(2.5);
}

// -------------------------------------------------------------
// Generate region code for a point
void setCode(PT &point)
{
    point.CODE[3] = (point.x < xmin) ? 1 : 0;   // LEFT
    point.CODE[2] = (point.x > xmax) ? 1 : 0;   // RIGHT
    point.CODE[1] = (point.y < ymin) ? 1 : 0;   // BOTTOM
    point.CODE[0] = (point.y > ymax) ? 1 : 0;   // TOP
}

// -------------------------------------------------------------
// Determine visibility
int setVisible(PT p1, PT p2)
{
    int flag = 1;
    PT ptemp;

    // trivial accept
    for(int i = 0; i < 4; i++)
        if (p1.CODE[i] != 0 || p2.CODE[i] != 0)
            flag = 0;

    if (flag) return 0;   // completely inside

    // trivial reject
    flag = 0;
    for(int i = 0; i < 4; i++)
        if (p1.CODE[i] == 1 && p2.CODE[i] == 1)
            return 1;   // completely outside

    return 2;           // needs clipping
}

// -------------------------------------------------------------
// Compute intersected point
PT pointIntersection(PT point, float m)
{
    float x = point.x, y = point.y;

    if (point.CODE[3] == 1) {       // LEFT
        x = xmin;
        y = m * (x - point.x) + point.y;
    }

    if (point.CODE[2] == 1) {       // RIGHT
        x = xmax;
        y = m * (x - point.x) + point.y;
    }

    if (point.CODE[1] == 1) {       // BOTTOM
        y = ymin;
        x = (y - point.y) / m + point.x;
    }

    if (point.CODE[0] == 1) {       // TOP
        y = ymax;
        x = (y - point.y) / m + point.x;
    }

    point.x = x;
    point.y = y;
    return point;
}

// -------------------------------------------------------------
// Cohen–Sutherland line clipping
void cohen_Line(PT p1, PT p2)
{
    PT ptemp;

    setCode(p1);
    setCode(p2);

    switch (setVisible(p1, p2))
    {
        case 0:   // fully visible
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(xmin + 500, ymin + 500);
                glVertex2f(xmin + 500, ymax + 500);
                glVertex2f(xmax + 500, ymax + 500);
                glVertex2f(xmax + 500, ymin + 500);
            glEnd();

            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
                glVertex2f(p1.x + 500, p1.y + 500);
                glVertex2f(p2.x + 500, p2.y + 500);
            glEnd();
            break;

        case 1:   // fully invisible
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(xmin + 500, ymin + 500);
                glVertex2f(xmin + 500, ymax + 500);
                glVertex2f(xmax + 500, ymax + 500);
                glVertex2f(xmax + 500, ymin + 500);
            glEnd();
            break;

        case 2:   // partially visible (clip)
            float m = (p2.y - p1.y) / (p2.x - p1.x);
            if (setVisible(p1, p2) == 2)
            {
                if (setVisible(p1, p2) == 2)
                {
                    if (p1.CODE[0] || p1.CODE[1] || p1.CODE[2] || p1.CODE[3])
                        p1 = pointIntersection(p1, m);
                    else
                        p2 = pointIntersection(p2, m);
                }
            }

            setCode(p1);
            setCode(p2);

            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
                glVertex2f(p1.x + 500, p1.y + 500);
                glVertex2f(p2.x + 500, p2.y + 500);
            glEnd();
            break;
    }
    glFlush();
}

// -------------------------------------------------------------

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // sample points (you can change)
    p1.x = -200; p1.y = -50;
    p2.x = 150;  p2.y = 200;

    cohen_Line(p1, p2);

    glFlush();
}

// -------------------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cohen Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
