#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to blue
    glColor3f(0.0, 0.0, 1.0);

    // Begin drawing the filled square
    glBegin(GL_POLYGON);
    glVertex2f(-3.0, 5.0); // Vertex 1
    glVertex2f(0.0, -4.0); // Vertex 2
    glVertex2f(3.0, 7.0);  // Vertex 3
    glVertex2f(6.0, -2.0); // Vertex 4
    glEnd();

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
    glutCreateWindow("Square");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
