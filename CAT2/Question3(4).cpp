#include <GL/glut.h>
#include <cmath>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to blue
    glColor3f(0.0, 0.0, 1.0);

    // Begin drawing the filled square
    glBegin(GL_POLYGON);
    glVertex2f(-3.0, 5.0); // Vertex 1
    glVertex2f(0.0, -4.0); // Vertex 2
    glVertex2f(3.0, 7.0);  // Vertex 3
    glEnd();

    // Draw the shadow square in dotted red lines
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF); // Dotted pattern
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_LINE_LOOP);
    glVertex2f(-3.0, 5.0); // Vertex 1
    glVertex2f(0.0, 5.0);  // Vertex 2
    glVertex2f(0.0, 7.0);  // Vertex 3
    glVertex2f(-3.0, 7.0); // Vertex 4
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glFlush();
}

void reflectAndDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to blue
    glColor3f(0.0, 0.0, 1.0);

    // Begin drawing the reflected square
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f); // Reflect across the Y-axis
    glBegin(GL_POLYGON);
    glVertex2f(-3.0, 5.0); // Vertex 1
    glVertex2f(0.0, -4.0); // Vertex 2
    glVertex2f(3.0, 7.0);  // Vertex 3
    glEnd();
    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Set the viewing area
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("Reflected Square");
    init();
    glutDisplayFunc(reflectAndDisplay); // Change display function to reflectAndDisplay
    glutMainLoop();
    return 0;
}
