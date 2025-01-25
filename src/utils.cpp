#include "../headers/utils.h"

GLfloat roundToDecimalPlaces(GLfloat value, int decimalPlaces) {
    GLfloat scale = std::pow(10.0f, decimalPlaces);
    return std::round(value * scale) / scale;
}