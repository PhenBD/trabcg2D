#include "../headers/player.h"

void Player::draw() {
    glPushMatrix();
        glColor3f(0, 255, 0);
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON);
            glVertex2d(0, 0);
            glVertex2d(width, 0);
            glVertex2d(width, height);
            glVertex2d(0, height);
        glEnd();
    glPopMatrix();
}

void Player::checkCollision(Object obj) {
    // Check collision on X and Y axes
    if (getRight() > obj.getLeft() && getLeft() < obj.getRight() &&
        getBottom() > obj.getTop() && getTop() < obj.getBottom()) {
        
        // Handle collision based on player's direction
        switch (getDirection()) {
            case RIGHT:
                setX(obj.getLeft() - getWidth());
                break;
            case LEFT:
                setX(obj.getRight());
                break;
            case UP:
                setY(obj.getBottom());
                break;
            case DOWN:
                setY(obj.getTop() - getHeight());
                break;
            default:
                break;
        }
    }
}

void Player::moveX(GLfloat dx) {
    setX(x + dx);
}

void Player::moveY(GLfloat dy) {
    setY(y + dy);
}