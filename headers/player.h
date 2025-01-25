#ifndef PLAYER_H
#define	PLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"
#include <iostream>

// Enum for directions of movement
enum Direction {UP, DOWN, LEFT, RIGHT};

class Player : public Object {

private:
    GLfloat walkSpeed = 0.05;
    GLfloat jumpSpeed = 0.2;
    int direction = RIGHT;

public:
    Player(){}; // Default constructor
    Player(GLfloat x, GLfloat y, GLfloat r) : Object(x - r, y - r, r, 2*r) {};
    void draw();
    void moveX(GLfloat dx);
    void moveY(GLfloat dy);
    void checkCollision(Object obj);

    void setDirection(int direction){
        this->direction = direction;
    };

    GLfloat getWalkSpeed(){
        return walkSpeed;
    };
    GLfloat getJumpSpeed(){
        return jumpSpeed;
    };
    int getDirection(){
        return direction;
    };
};

#endif	/* PLAYER_H */