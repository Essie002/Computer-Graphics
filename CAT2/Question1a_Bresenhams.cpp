#include <GL/glut.h>
#include <cmath>

void drawCircle(int centerX, int centerY, int radius) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glBegin(GL_POLYGON); // Fill the circle
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(3, 3, 4); // Center 3,3 radius 4
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 10, 0, 10); // Set the viewing area
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Bresenham Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
