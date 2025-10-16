#include <GL/glut.h>


const int n = 4;


float x[n] = {250, 150, 250, 350};
float y[n] = {200, 300, 400, 300};

int le[500], re[500];

void draw_pixel(int x, int y) {
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void edgedetect(float x1, float y1, float x2, float y2) {
    float mx, x;
    int i;

    if (y2 < y1) {
        float temp;
        temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }

    if ((y2 - y1) != 0)
        mx = (x2 - x1) / (y2 - y1);
    else
        mx = 0;

    x = x1;
    for (i = int(y1); i <= int(y2); i++) {
        if (x < le[i]) le[i] = int(x);
        if (x > re[i]) re[i] = int(x);
        x += mx;
    }
}

void scanfill() {
    for (int i = 0; i < 500; i++) {
        le[i] = 500;
        re[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        edgedetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }

    for (int y = 0; y < 500; y++) {
        if (le[y] <= re[y]) {
            for (int i = le[y]; i <= re[y]; i++) {
                draw_pixel(i, y);
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(x[i], y[i]);
    }
    glEnd();


    scanfill();
    glFlush();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan Line Polygon Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
