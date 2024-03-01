#include <GL/glut.h>
#include <cmath>

void drawCircle(int centerX, int centerY, int radius) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glBegin(GL_POLYGON); // Begin drawing filled polygon
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(centerX + x, centerY + y); // Plot points
    }
    glEnd(); // End drawing
    glFlush(); // Flush drawing commands
}

void drawDiameter(int centerX, int centerY, int radius) {
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
    glBegin(GL_LINES);
    glVertex2f(centerX - radius, centerY); // Start point
    glVertex2f(centerX + radius, centerY); // End point
    glEnd();
    glFlush(); // Flush drawing commands
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
    drawCircle(3, 3, 4); // Draw circle centered at (3,3) with radius 4
    drawDiameter(3, 3, 4); // Draw diameter
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 6, 0, 6); // Set the viewing area
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(600, 600); // Set window size to a square (400x400)
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Midpoint Circle Drawing Algorithm"); // Create window with title
    init(); // Initialize OpenGL parameters
    glutDisplayFunc(display); // Set display function
    glutMainLoop(); // Enter main event loop
    return 0;
}

