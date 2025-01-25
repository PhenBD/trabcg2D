#ifndef CHARACTER_H
#define	CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"
#include "arena.h"
#include <iostream>

// Enum for directions of movement
enum Direction {UP, DOWN, LEFT, RIGHT};

class Character : public Object {

protected:
    GLfloat thetaLeft1 = 45;
    GLfloat thetaLeft2 = 45;
    GLfloat thetaRight1 = -45;
    GLfloat thetaRight2 = 45;
    GLfloat thetaArm = -45;

private:
    int direction = RIGHT;
    int lookingDirection = RIGHT;

    void drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void drawCirc(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void drawArm(GLfloat x, GLfloat y, GLfloat theta);
    void drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeft1, GLfloat thetaLeft2, GLfloat thetaRight1, GLfloat thetaRight2);

public:
    Character(){}; // Default constructor
    Character(GLfloat x, GLfloat y, GLfloat r) : Object(x - r, y - r, r/2, 2*r) {};
    void draw(GLfloat R, GLfloat G, GLfloat B);
    void moveX(GLfloat dx);
    void moveY(GLfloat dy);
    int checkCollision(Object obj);
    int checkArenaCollision(Arena arena);
    void flipDirection();

    void setDirection(int direction){
        this->direction = direction;
    };
    void setLookingDirection(int direction){
        this->lookingDirection = direction;
    };
    void setThetaArm(GLfloat theta){
        this->thetaArm = theta;
    };

    int getDirection(){
        return direction;
    };
    int getLookingDirection(){
        return lookingDirection;
    };
};

#endif	/* CHARACTER_H */