#include "../headers/player.h"

void Player::draw() {
    glPushMatrix();
        glColor3f(0, 255, 0);
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2f(-width/2, 0);
            glVertex2f(-width/2, -height);
            glVertex2f(width/2, -height);
            glVertex2f(width/2, 0);
        glEnd();
    glPopMatrix();
}

void Player::moveX(GLfloat dx) {
    setX(x + dx);
}

void Player::moveY(GLfloat dy) {
    setY(y + dy);
}