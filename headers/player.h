#ifndef PLAYER_H
#define	PLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"

class Player : public Object {

private:
    GLfloat walkSpeed = 0.05;
    GLfloat jumpSpeed = 0.2;

public:
    Player(){}; // Default constructor
    Player(GLfloat x, GLfloat y, GLfloat r) : Object(x, y, r, 2*r) {};
    void draw();
    void moveX(GLfloat dx);
    void moveY(GLfloat dy);

    GLfloat getWalkSpeed(){
        return walkSpeed;
    };
    GLfloat getJumpSpeed(){
        return jumpSpeed;
    };
};

#endif	/* PLAYER_H */