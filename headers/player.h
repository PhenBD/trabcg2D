#ifndef PLAYER_H
#define	PLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.h"
#include <iostream>

class Player : public Character {

private:
    GLfloat walkSpeed = 0.04;
    GLfloat jumpSpeed;
    bool onAir = false;
    bool jumping = false;
    int jumpingTime = 0;

public:
    Player(){}; // Default constructor
    Player(GLfloat x, GLfloat y, GLfloat r) : Character(x, y, r) {
        jumpSpeed = ((height * 3) / 2000) * 2;
    };
    void draw(){
        Character::draw(0.0, 1.0, 0.0);
    }

    void setJumping(bool jumping){
        this->jumping = jumping;
    };
    void setJumpingTime(int time){
        jumpingTime = time;
    };
    void addJumpingTime(int time){
        jumpingTime += time;
    };
    void setOnAir(bool onAir){
        this->onAir = onAir;
    };

    GLfloat getWalkSpeed(){
        return walkSpeed;
    };
    GLfloat getJumpSpeed(){
        return jumpSpeed;
    };
    bool isJumping(){
        return jumping;
    };
    int getJumpingTime(){
        return jumpingTime;
    };
    bool isOnAir(){
        return onAir;
    };
};

#endif	/* PLAYER_H */