#ifndef ENEMY_H
#define	ENEMY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"

class Enemy : public Object {

private:
    GLfloat walkSpeed = 0.05;

public:
    Enemy(){}; // Default constructor
    Enemy(GLfloat x, GLfloat y, GLfloat r) : Object(x, y, r, 2*r) {};
    void draw();

    GLfloat getWalkSpeed(){
        return walkSpeed;
    };
};

#endif	/* ENEMY_H */

