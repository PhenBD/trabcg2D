#include "../headers/enemy.h"

void Enemy::draw() {
    glPushMatrix();
        glColor3f(255, 0, 0);
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2d(0, 0);
            glVertex2d(width, 0);
            glVertex2d(width, height);
            glVertex2d(0, height);
        glEnd();
    glPopMatrix();
}