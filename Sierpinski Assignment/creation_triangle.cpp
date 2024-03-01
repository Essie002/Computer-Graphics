#include <GL/glut.h>

// Define vertices of the initial triangle
GLfloat vertices[3][2] = {{-1.0, -0.5}, {1.0, -0.5}, {0.0, 1.0}};

// Function to draw a triangle with specified color
void drawTriangle(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat color[]) {
    glColor3fv(color);
    glBegin(GL_TRIANGLES);
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    glEnd();
}

// Function to divide a triangle and draw the smaller triangles
void divideTriangle(GLfloat v1[], GLfloat v2[], GLfloat v3[], int m) {
    GLfloat v12[2], v23[2], v31[2];
    int j;
    if(m > 0) {
        // Calculate midpoints of edges
        for(j = 0; j < 2; j++) v12[j] = (v1[j] + v2[j]) / 2;
        for(j = 0; j < 2; j++) v23[j] = (v2[j] + v3[j]) / 2;
        for(j = 0; j < 2; j++) v31[j] = (v3[j] + v1[j]) / 2;
        // Recursively divide the triangle
        divideTriangle(v1, v12, v31, m-1);
        divideTriangle(v12, v2, v23, m-1);
        divideTriangle(v31, v23, v3, m-1);
    }
    else {
        // Set colors for each triangle
        GLfloat colors[3][3] = {{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}}; // Black, Green, Yellow
        // Draw triangles with different colors
        drawTriangle(v1, v2, v3, colors[rand()%3]);
    }
}

// Function to display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    divideTriangle(vertices[0], vertices[1], vertices[2], 5); // Change the last argument to control the recursion depth
    glFlush();
}

// Function to initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
