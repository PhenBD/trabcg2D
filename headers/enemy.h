#ifndef ENEMY_H
#define	ENEMY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.h"

class Enemy : public Character {

private:
    GLfloat walkSpeed = 0.01;
    int walkingDirection = RIGHT;

public:
    Enemy(){}; // Default constructor
    Enemy(GLfloat x, GLfloat y, GLfloat r) : Character(x, y, r) {};
    void draw(){
        Character::draw(1.0, 0.5, 0.0);
    }

    void setWalkingDirection(int direction){
        walkingDirection = direction;
    };

    GLfloat getWalkSpeed(){
        return walkSpeed;
    };
    GLfloat getWalkingDirection(){
        return walkingDirection;
    };
};

#endif	/* ENEMY_H */

