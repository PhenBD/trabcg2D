#include "../headers/object.h"

Object::Object(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
    this->x = roundToDecimalPlaces(x, 5);
    this->y = roundToDecimalPlaces(y, 5);
    this->width = roundToDecimalPlaces(width, 5);
    this->height = roundToDecimalPlaces(height, 5);
    right = x + width;
    left = x;
    top = y;
    bottom = y + height;
};

void Object::setX(GLfloat x){
    this->x = x;
    right = x + width;
    left = x;
};

void Object::setY(GLfloat y){
    this->y = y;
    top = y;
    bottom = y + height;
};