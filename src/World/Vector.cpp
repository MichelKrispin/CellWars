#include "Vector.h"

Vector::Vector()
    : X(0), Y(0)
{}

Vector::Vector(unsigned int x, unsigned int y)
    : X(x), Y(y)
{}

Vector::~Vector()
{}

bool Vector::operator==(Vector &other)
{
    return (X == other.X && Y == other.Y);
}