#ifndef OBJECT_H
#define	OBJECT_H
#include <GL/gl.h>
#include <GL/glu.h>

class Object {

protected:
    GLfloat x;
    GLfloat y;
    GLfloat height;
    GLfloat width;
    GLfloat right;
    GLfloat left;
    GLfloat top;
    GLfloat bottom;

public:
    Object(){
        x = 0;
        y = 0;
        height = 0;
        width = 0;
        right = 0;
        left = 0;
        top = 0;
        bottom = 0;
    }

    Object(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

    void setX(GLfloat x);
    void setY(GLfloat y);

    GLfloat getX(){
        return x;
    };
    GLfloat getY(){
        return y;
    };
    GLfloat getHeight(){
        return height;
    };
    GLfloat getWidth(){
        return width;
    };
    GLfloat getRight(){
        return right;
    };
    GLfloat getLeft(){
        return left;
    };
    GLfloat getTop(){
        return top;
    };
    GLfloat getBottom(){
        return bottom;
    };
};

#endif	/* OBJECT_H */