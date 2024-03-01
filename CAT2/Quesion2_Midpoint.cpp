#include <GL/glut.h>
#include <iostream>

int width = 800;
int height = 600;

void plot(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
}

void drawEllipse() {
    int rx = width / 2;
    int ry = height / 2;
    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int twoRx2 = 2 * rx2;
    int twoRy2 = 2 * ry2;
    int p;
    int x = 0;
    int y = ry;
    int px = 0;
    int py = twoRx2 * y;

    glBegin(GL_POLYGON); // Use GL_POLYGON to fill the ellipse
    // Region 1
    p = ry2 - (rx2 * ry) + (0.25 * rx2);
    while (px < py) {
        x++;
        px += twoRy2;
        if (p < 0)
            p += ry2 + px;
        else {
            y--;
            py -= twoRx2;
            p += ry2 + px - py;
        }
        plot(x, y);
    }

    // Region 2
    p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y > 0) {
        y--;
        py -= twoRx2;
        if (p > 0)
            p += rx2 - py;
        else {
            x++;
            px += twoRy2;
            p += rx2 - py + px;
        }
        plot(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0); // Green color
    drawEllipse();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    width = w;
    height = h;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();
    return 0;
}
