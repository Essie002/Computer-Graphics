#include <GL/glut.h>

// Define vertices of the initial triangle
GLfloat vertices[3][2] = {{-1.0, -0.5}, {1.0, -0.5}, {0.0, 1.0}};
// Original triangle vertices
GLfloat originalVertices[3][2] = {{-1.0, -0.5}, {1.0, -0.5}, {0.0, 1.0}};

// Function to draw a triangle with specified color
void drawTriangle(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat color[]) {
    // Set the color
    glColor3fv(color);
    // Begin drawing triangles
    glBegin(GL_TRIANGLES);
    // Define vertices of the triangle
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    // End drawing
    glEnd();
}

// Function to check if a point lies inside the original triangle
bool isInsideOriginalTriangle(GLfloat point[]) {
    // Using barycentric coordinates to check if the point lies inside the triangle
    GLfloat u, v, w;
    GLfloat v0[2] = {originalVertices[1][0] - originalVertices[0][0], originalVertices[1][1] - originalVertices[0][1]};
    GLfloat v1[2] = {originalVertices[2][0] - originalVertices[0][0], originalVertices[2][1] - originalVertices[0][1]};
    GLfloat v2[2] = {point[0] - originalVertices[0][0], point[1] - originalVertices[0][1]};
    // Compute dot products
    float dot00 = v0[0] * v0[0] + v0[1] * v0[1];
    float dot01 = v0[0] * v1[0] + v0[1] * v1[1];
    float dot02 = v0[0] * v2[0] + v0[1] * v2[1];
    float dot11 = v1[0] * v1[0] + v1[1] * v1[1];
    float dot12 = v1[0] * v2[0] + v1[1] * v2[1];
    // Compute barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    w = 1.0f - u - v;
    // Check if point lies inside the triangle
    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

// Function to clip the Sierpinski Triangle back to the original triangle
void clipToOriginalTriangle(GLfloat v1[], GLfloat v2[], GLfloat v3[], int m) {
    // Check if any vertex of the triangle lies inside the original triangle
    if (isInsideOriginalTriangle(v1) || isInsideOriginalTriangle(v2) || isInsideOriginalTriangle(v3)) {
        // If any vertex lies inside, draw the triangle
        GLfloat color[3] = {0.0, 0.0, 0.0}; // Black color
        drawTriangle(v1, v2, v3, color);
    } else {
        // Otherwise, clip the triangle further
        GLfloat v12[2], v23[2], v31[2];
        int j;
        // Calculate midpoints of edges
        for(j = 0; j < 2; j++) v12[j] = (v1[j] + v2[j]) / 2;
        for(j = 0; j < 2; j++) v23[j] = (v2[j] + v3[j]) / 2;
        for(j = 0; j < 2; j++) v31[j] = (v3[j] + v1[j]) / 2;
        // Recursively clip the triangle
        clipToOriginalTriangle(v1, v12, v31, m-1);
        clipToOriginalTriangle(v12, v2, v23, m-1);
        clipToOriginalTriangle(v31, v23, v3, m-1);
    }
}

// Function to display callback
void display() {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // Clip the Sierpinski Triangle back to the original triangle
    clipToOriginalTriangle(vertices[0], vertices[1], vertices[2], 5); // Change the last argument to control the recursion depth
    // Flush the drawing commands
    glFlush();
}

// Function to initialize OpenGL
void init() {
    // Set the clear color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // Set the matrix mode to projection
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // Set the viewing volume
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

// Main function
int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Back-clipped Sierpinski Triangle");
    // Initialize OpenGL
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
