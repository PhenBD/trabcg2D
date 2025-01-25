#ifndef PLAYER_H
#define	PLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"
#include "arena.h"
#include <iostream>

// Enum for directions of movement
enum Direction {UP, DOWN, LEFT, RIGHT};

class Player : public Object {

private:
    GLfloat walkSpeed = 0.04;
    GLfloat jumpSpeed;
    bool onAir = false;
    bool jumping = false;
    int jumpingTime = 0;
    int direction = RIGHT;

public:
    Player(){}; // Default constructor
    Player(GLfloat x, GLfloat y, GLfloat r) : Object(x - r, y - r, r, 2*r) {
        jumpSpeed = ((height * 3) / 2000) * 2;
    };
    void draw();
    void moveX(GLfloat dx);
    void moveY(GLfloat dy);
    bool checkCollision(Object obj);
    bool checkArenaCollision(Arena arena);

    void setDirection(int direction){
        this->direction = direction;
    };
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
    int getDirection(){
        return direction;
    };
    bool isOnAir(){
        return onAir;
    };
};

#endif	/* PLAYER_H */