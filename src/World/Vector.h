#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector
{
    /**
     * \brief Initialize the Vector with position 0 and 0.
     */
    Vector();

    /**
     * \brief Initialize the Vector with position x and y.
     *
     * \param x The X value of this Vector.
     * \param y The Y value of this Vector.
     */
    Vector(unsigned int x, unsigned int y);

    virtual ~Vector();

    /**
     * \brief Checks for X and Y the equality.
     *
     * \param other Another vector.
     */
    bool operator==(Vector &other);

    unsigned short X; //< The X position of this Vector.
    unsigned short Y; //< The Y position of this Vector.
};

#endif
