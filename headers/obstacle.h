#ifndef OBSTACLE_H
#define	OBSTACLE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"

class Obstacle : public Object {

public:
    Obstacle(){};
    Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height) : Object(x, y, width, height) {};
    void draw();
};

#endif	/* OBSTACLE_H */