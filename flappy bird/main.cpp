
// bird_flypi.cpp
// Simple Flappy-Bird-like demo using FreeGLUT + legacy OpenGL
// Compile with: g++ -o flypi bird_flypi.cpp -lfreeglut -lopengl32 -lglu32

#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

const int WINDOW_W = 800;
const int WINDOW_H = 600;

// Bird properties
float birdX = WINDOW_W * 0.25f;
float birdY = WINDOW_H * 0.5f;
float birdRadius = 18.0f;
float birdVel = 0.0f;

// Physics
const float GRAVITY = -900.0f;    // pixels / s^2 (negative = down)
const float FLAP_VELOCITY = 330.0f; // pixels / s
const float MAX_FALL_SPEED = -700.0f;

// Timing
int lastTime = 0;

// Pipes
struct Pipe {
    float x;
    float gapY;   // center of gap (pixels)
    float gapH;   // gap height
    bool scored;
};
std::vector<Pipe> pipes;
const float PIPE_WIDTH = 80.0f;
const float PIPE_SPEED = 200.0f; // pixels / s
const float PIPE_SPAWN_INTERVAL = 1.6f; // seconds
float spawnTimer = 0.0f;

// Game state
bool running = true;
bool gameOver = false;
int score = 0;

// Utilities
float randf(float a, float b) {
    return a + static_cast<float>(rand()) / RAND_MAX * (b - a);
}

void drawText(float x, float y, const std::string& s, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (char c : s) glutBitmapCharacter(font, c);
}

// draw filled circle
void drawCircle(float cx, float cy, float r, int segments = 36) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float a = (2.0f * 3.1415926f * i) / segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

// reset game
void resetGame() {
    pipes.clear();
    birdY = WINDOW_H * 0.5f;
    birdVel = 0.0f;
    spawnTimer = 0.0f;
    score = 0;
    gameOver = false;
    running = true;
}

// window coordinate setup
void setupOrtho() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// collision AABB check between circle and rectangle
bool circleRectCollision(float cx, float cy, float r, float rx, float ry, float rw, float rh) {
    // rectangle (rx, ry) is bottom-left
    float closestX = std::max(rx, std::min(cx, rx + rw));
    float closestY = std::max(ry, std::min(cy, ry + rh));
    float dx = cx - closestX;
    float dy = cy - closestY;
    return (dx*dx + dy*dy) < (r*r);
}

void updateScene(float dt) {
    if (!running || gameOver) return;

    // physics
    birdVel += GRAVITY * dt;
    if (birdVel < MAX_FALL_SPEED) birdVel = MAX_FALL_SPEED;
    birdY += birdVel * dt;

    // spawn pipes
    spawnTimer += dt;
    if (spawnTimer >= PIPE_SPAWN_INTERVAL) {
        spawnTimer = 0.0f;
        Pipe p;
        p.x = WINDOW_W + 50.0f;
        p.gapH = 150.0f + randf(-30.0f, 30.0f);
        p.gapY = 140.0f + randf(0.0f, WINDOW_H - 280.0f);
        p.scored = false;
        pipes.push_back(p);
    }

    // move pipes and handle scoring/collision
    for (int i = 0; i < (int)pipes.size(); ++i) {
        pipes[i].x -= PIPE_SPEED * dt;

        // scoring: if bird passed the pipe center and not yet scored
        if (!pipes[i].scored && pipes[i].x + PIPE_WIDTH/2.0f < birdX) {
            pipes[i].scored = true;
            score++;
        }
    }

    // remove off-screen pipes
    while (!pipes.empty() && pipes.front().x + PIPE_WIDTH < -50.0f) {
        pipes.erase(pipes.begin());
    }

    // collision with ground or ceiling
    if (birdY - birdRadius <= 0.0f || birdY + birdRadius >= WINDOW_H) {
        gameOver = true;
        running = false;
        return;
    }

    // collision with pipes
    for (const auto& p : pipes) {
        float topRx = p.x;
        float topRy = p.gapY + p.gapH/2.0f;
        float topRw = PIPE_WIDTH;
        float topRh = WINDOW_H - topRy;

        float botRx = p.x;
        float botRy = 0.0f;
        float botRw = PIPE_WIDTH;
        float botRh = p.gapY - p.gapH/2.0f;

        if (circleRectCollision(birdX, birdY, birdRadius, topRx, topRy, topRw, topRh) ||
            circleRectCollision(birdX, birdY, birdRadius, botRx, botRy, botRw, botRh)) {
            gameOver = true;
            running = false;
            return;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // sky gradient background (simple two-rect trick)
    glBegin(GL_QUADS);
    // top
    glColor3f(0.529f, 0.808f, 0.922f); // sky blue
    glVertex2f(0, WINDOW_H);
    glVertex2f(WINDOW_W, WINDOW_H);
    // bottom
    glColor3f(0.741f, 0.902f, 0.960f);
    glVertex2f(WINDOW_W, 0);
    glVertex2f(0, 0);
    glEnd();

    // ground
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(WINDOW_W, 0);
    glVertex2f(WINDOW_W, 40);
    glVertex2f(0, 40);
    glEnd();

    // draw pipes
    for (const auto& p : pipes) {
        // bottom pipe
        glColor3f(0.1f, 0.6f, 0.1f);
        glBegin(GL_QUADS);
        glVertex2f(p.x, 0);
        glVertex2f(p.x + PIPE_WIDTH, 0);
        glVertex2f(p.x + PIPE_WIDTH, p.gapY - p.gapH/2.0f);
        glVertex2f(p.x, p.gapY - p.gapH/2.0f);
        glEnd();

        // top pipe
        glBegin(GL_QUADS);
        glVertex2f(p.x, p.gapY + p.gapH/2.0f);
        glVertex2f(p.x + PIPE_WIDTH, p.gapY + p.gapH/2.0f);
        glVertex2f(p.x + PIPE_WIDTH, WINDOW_H);
        glVertex2f(p.x, WINDOW_H);
        glEnd();

        // pipe edges
        glColor3f(0.0f, 0.45f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(p.x, 0);
        glVertex2f(p.x + PIPE_WIDTH, 0);
        glVertex2f(p.x + PIPE_WIDTH, p.gapY - p.gapH/2.0f);
        glVertex2f(p.x, p.gapY - p.gapH/2.0f);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(p.x, p.gapY + p.gapH/2.0f);
        glVertex2f(p.x + PIPE_WIDTH, p.gapY + p.gapH/2.0f);
        glVertex2f(p.x + PIPE_WIDTH, WINDOW_H);
        glVertex2f(p.x, WINDOW_H);
        glEnd();
    }

    // draw bird (circle + eye + wing)
    glPushMatrix();
    glTranslatef(0, 0, 0);

    // body
    glColor3f(1.0f, 0.85f, 0.2f); // yellow
    drawCircle(birdX, birdY, birdRadius, 40);

    // belly
    glColor3f(1.0f, 0.95f, 0.6f);
    drawCircle(birdX - 4.0f, birdY - 3.0f, birdRadius*0.6f, 30);

    // eye
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(birdX + 8.0f, birdY + 6.0f, birdRadius*0.28f, 12);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(birdX + 10.0f, birdY + 8.0f, birdRadius*0.12f, 12);

    // beak (triangle)
    glColor3f(1.0f, 0.55f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(birdX + 18.0f, birdY + 2.0f);
    glVertex2f(birdX + 30.0f, birdY + 6.0f);
    glVertex2f(birdX + 18.0f, birdY - 4.0f);
    glEnd();

    glPopMatrix();

    // HUD / score
    std::ostringstream ss;
    ss << "Score: " << score;
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(10.0f, WINDOW_H - 24.0f, ss.str());

    if (gameOver) {
        std::string msg = "Game Over! Press R to Restart";
        int len = msg.length();
        glColor3f(0.8f, 0.0f, 0.0f);
        drawText(WINDOW_W*0.5f - 150, WINDOW_H*0.5f + 10, msg, GLUT_BITMAP_HELVETICA_18);

        std::ostringstream ss2;
        ss2 << "Final Score: " << score;
        drawText(WINDOW_W*0.5f - 80, WINDOW_H*0.5f - 20, ss2.str(), GLUT_BITMAP_HELVETICA_18);
    }

    glutSwapBuffers();
}

void idle() {
    int t = glutGet(GLUT_ELAPSED_TIME);
    if (lastTime == 0) lastTime = t;
    int elapsed = t - lastTime;
    lastTime = t;
    float dt = elapsed / 1000.0f;

    updateScene(dt);
    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (key == 27) { // ESC
        exit(0);
    } else if (key == ' ' && !gameOver) {
        // flap
        birdVel = FLAP_VELOCITY;
    } else if ((key == 'r' || key == 'R') && gameOver) {
        resetGame();
    }
}

void mouseClick(int button, int state, int x, int y) {
    (void)x; (void)y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !gameOver) {
        birdVel = FLAP_VELOCITY;
    }
}

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("Flypi Bird - OpenGL (FreeGLUT)");

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    setupOrtho();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyDown);
    glutMouseFunc(mouseClick);

    resetGame();
    lastTime = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();
    return 0;
}
