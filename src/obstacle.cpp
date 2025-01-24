#include "../headers/obstacle.h"

void Obstacle::draw() {
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2f(0, 0);
            glVertex2f(width, 0);
            glVertex2f(width, height);
            glVertex2f(0, height);
        glEnd();
    glPopMatrix();
}