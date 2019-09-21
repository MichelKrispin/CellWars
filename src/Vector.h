#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector
{
    /**
     * \brief Initialize the Vector with position 0 and 0.
     */
    Vector(): X(0), Y(0) {}
    /**
     * \brief Initialize the Vector with position x and y.
     */
    Vector(unsigned int x, unsigned int y): X(x), Y(y) {}

    unsigned short X; //< The X position of this Vector.
    unsigned short Y; //< The Y position of this Vector.

    /**
     * \brief Check for X and Y the equality.
     *
     * \param other Another vector
     */
    bool operator==(Vector &other)
    {
        return (X == other.X && Y == other.Y);
    }
};

#endif
