#include "../headers/character.h"

void Character::drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
        glColor3f(R, G, B);
        glBegin(GL_POLYGON);
            glVertex2f(-width/2, 0);
            glVertex2f(width/2, 0);
            glVertex2f(width/2, height);
            glVertex2f(-width/2, height);
        glEnd();
    glPopMatrix();
}

void Character::drawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
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
    glPopMatrix();
}

void Character::drawArm(GLfloat x, GLfloat y, GLfloat theta)
{
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(theta, 0, 0, 1);
        drawRect(height * 0.25, height * 0.05, 1.0, 1.0, 0.0);
    glPopMatrix();
}

void Character::drawLegs(GLfloat x, GLfloat y){
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
        drawLegs(0, 0.3 * height);
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

void Character::moveX(GLfloat dx, GLdouble timeDiff) {
    if (walking){
        if (lookingDirection == LEFT){
            thetaLeft1 += -legsAnimation * timeDiff;
            thetaLeft2 += -legsAnimation / 1.5 * timeDiff;
            thetaRight1 += legsAnimation * timeDiff;
            thetaRight2 += -legsAnimation / 1.5 * timeDiff;
        }
        else if (lookingDirection == RIGHT){
            thetaLeft1 += legsAnimation * timeDiff;
            thetaLeft2 += legsAnimation / 1.5 * timeDiff;
            thetaRight1 += -legsAnimation * timeDiff;
            thetaRight2 += legsAnimation / 1.5 * timeDiff;
        }

        if (thetaLeft1 > 45 || thetaLeft1 < -45 || thetaRight2 > 45 || thetaRight2 < -45){
            legsAnimation *= -1;
        }
        if ((thetaLeft1 > 0 || thetaLeft2 > 0 || thetaRight1 < 0 || thetaRight2 > 0) && lookingDirection == LEFT){
            legsAnimation *= -1;
        }
        else if ((thetaLeft1 < 0 || thetaLeft2 < 0 || thetaRight1 > 0 || thetaRight2 < 0) && lookingDirection == RIGHT){
            legsAnimation *= -1;
        }
    }
    else {
        thetaLeft1 = 0;
        thetaLeft2 = 0;
        thetaRight1 = 0;
        thetaRight2 = 0;
    }
    
    setX(x + dx * timeDiff);
}

void Character::moveY(GLfloat dy, GLdouble timeDiff) {
    setY(y + dy * timeDiff);
}

void Character::shoot(std::list<Shoot> &shoots){
    int ySignal = 1, xSignal = 1;
    if (getThetaArm() < -90 || getThetaArm() > 90)
        ySignal = -1;
    if (getThetaArm() > 0)
        xSignal = -1;

    GLfloat xs = getX() + (width / 2) + (xSignal * height * 0.25 * abs(sin(getThetaArm() * (M_PI / 180.0))));
    GLfloat ys = getY() + (0.4 * height) + (ySignal * height * 0.25 * abs(cos(getThetaArm() * (M_PI / 180.0))));
    Shoot shoot(xs, ys, getThetaArm() + 90, walkSpeed * 2, height * 0.07, player);
    shoots.push_back(shoot);
}