#include "../headers/character.h"

void Character::drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    glEnd();
}

void Character::drawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0); // Centro do círculo
        for (int i = 0; i <= 360; i+=20)
        {
            GLfloat radians = i * M_PI / 180.0;

            GLfloat x = radius * cos(radians);
            GLfloat y = radius * sin(radians);
            glVertex2f(x, y);
        }
    glEnd();
}

void Character::drawArm(GLfloat x, GLfloat y, GLfloat theta)
{
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(theta, 0, 0, 1);
        drawRect(height * 0.25, height * 0.05, 1.0, 1.0, 0.0);
    glPopMatrix();
}

void Character::drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeft1, GLfloat thetaLeft2, GLfloat thetaRight1, GLfloat thetaRight2){
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(thetaLeft1, 0, 0, 1);
        drawRect(height * 0.22, height * 0.05, 1.0, 0.0, 0.0);
        glTranslatef(0, height * 0.22, 0);
        glRotatef(thetaLeft2, 0, 0, 1);
        drawRect(height * 0.22, height * 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(thetaRight1, 0, 0, 1);
        drawRect(height * 0.22, height * 0.05, 1.0, 0.0, 0.0);
        glTranslatef(0, height * 0.22, 0);
        glRotatef(thetaRight2, 0, 0, 1);
        drawRect(height * 0.22, height * 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();
}

void Character::draw(GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
        glTranslatef(x + (width/2), y + (0.15 * height), 0);
        drawCirc((0.15 * height), R, G, B);
        glTranslatef(0, (0.15 * height), 0);
        drawRect(0.3 * height, width, R, G, B);
        drawArm(0, 0.1 * height, thetaArm);
        drawLegs(0, 0.3 * height, thetaLeft1, thetaLeft2, thetaRight1, thetaRight2);
    glPopMatrix();
}

int Character::checkCollision(Object obj) {
    // Check collision on X and Y axes
    if (getRight() > obj.getLeft() && getLeft() < obj.getRight() &&
        getBottom() > obj.getTop() && getTop() < obj.getBottom()) {
        
        // Handle collision based on Character's direction
        switch (getDirection()) {
            case RIGHT:
                setX(obj.getLeft() - getWidth());
                return RIGHT;
            case LEFT:
                setX(obj.getRight());
                return LEFT;
            case UP:
                setY(obj.getBottom());
                return UP;
            case DOWN:
                setY(obj.getTop() - getHeight());
                return DOWN;
            default:
                break;
        }
    }

    return -1;
}

int Character::checkArenaCollision(Arena arena){
    // X axis
    if (getLeft() < arena.getLeft())
    {
        setX(arena.getLeft());
        return LEFT;
    }
    else if (getRight() > arena.getRight()) 
    {
        setX(arena.getRight() - getWidth());
        return RIGHT;
    }
    // Y axis
    if (getTop() < arena.getTop())
    {
        setY(arena.getTop());
        return UP;
    }
    else if (getBottom() > arena.getBottom()) 
    {
        setY(arena.getBottom() - getHeight());
        return DOWN;
    }

    return -1;
}

void Character::flipDirection() {
    thetaArm *= -1;
    thetaLeft1 *= -1;
    thetaLeft2 *= -1;
    thetaRight1 *= -1;
    thetaRight2 *= -1;
}

void Character::moveX(GLfloat dx) {
    setX(x + dx);
}

void Character::moveY(GLfloat dy) {
    setY(y + dy);
}