#include "../headers/enemy.h"
#include <iostream>

void Enemy::draw() {
    glPushMatrix();
        glColor3f(255, 0, 0);
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2f(-width/2, 0);
            glVertex2f(-width/2, -height);
            glVertex2f(width/2, -height);
            glVertex2f(width/2, 0);
        glEnd();
    glPopMatrix();
}