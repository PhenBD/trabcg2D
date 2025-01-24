#include "../headers/object.h"

Object::Object(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    right = x + width/2;
    left = x - width/2;
    top = y - height/2;
    bottom = y + height/2;
};

void Object::setX(GLfloat x){
    this->x = x;
    right = x + width/2;
    left = x - width/2;
};

void Object::setY(GLfloat y){
    this->y = y;
    top = y - height/2;
    bottom = y + height/2;
};