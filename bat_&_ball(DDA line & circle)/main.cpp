#include <GL/glut.h>
#include <cmath>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(0, 600, 0, 600);       // Set coordinate system
}

// DDA Line Drawing Algorithm
void ddaLine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Draw circle using short DDA line segments
void drawCircle(float xc, float yc, float r) {
    int segments = 100;
    float step = 2 * 3.14159 / segments;
    for (int i = 0; i < segments; i++) {
        float x1 = xc + r * cos(i * step);
        float y1 = yc + r * sin(i * step);
        float x2 = xc + r * cos((i + 1) * step);
        float y2 = yc + r * sin((i + 1) * step);
        ddaLine(x1, y1, x2, y2);
    }
}

// Draw a rotated rectangle centered at (cx,cy) with given length & width
void drawRotatedRect(float cx, float cy, float length, float width, float angleRad) {
    float hl = length / 2.0, hw = width / 2.0;

    float pts[4][2] = {
        {-hl, -hw}, {hl, -hw},
        {hl, hw}, {-hl, hw}
    };

    // Rotate and translate points
    for (int i = 0; i < 4; i++) {
        float x = pts[i][0], y = pts[i][1];
        float xr = x * cos(angleRad) - y * sin(angleRad) + cx;
        float yr = x * sin(angleRad) + y * cos(angleRad) + cy;
        pts[i][0] = xr;
        pts[i][1] = yr;
    }

    // Draw edges
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        ddaLine(pts[i][0], pts[i][1], pts[j][0], pts[j][1]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float cx = 300, cy = 250;          // Center of bat blade
    float bladeLen = 200, bladeWid = 30;
    float angle = 45 * 3.14159 / 180.0;

    // --- Draw Blade ---
    glColor3f(0, 0, 0); // Black
    drawRotatedRect(cx, cy, bladeLen, bladeWid, angle);

    // --- Draw Handle ---
    float hx = cx + (bladeLen / 2.0 + 30) * cos(angle);
    float hy = cy + (bladeLen / 2.0 + 30) * sin(angle);
    float handleLen = 60, handleWid = 10;
    drawRotatedRect(hx, hy, handleLen, handleWid, angle);

    // --- Draw Ball approaching sweet spot from further left ---
    float sweetOffset = bladeLen / 4.0;
    float ballX = cx - sweetOffset * cos(angle) - 50; // Shifted 50 units left
    float ballY = cy - sweetOffset * sin(angle);
    glColor3f(1, 0, 0); // Red
    drawCircle(ballX, ballY, 20);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bat and Ball using DDA Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
