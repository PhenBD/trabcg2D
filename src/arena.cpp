#include "../headers/arena.h"

void Arena::draw() {
    glColor3f(0, 0, 255);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    glEnd();
}