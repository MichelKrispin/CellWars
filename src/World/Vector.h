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
    bool operator==(const Vector &other) const;

    /**
     * \brief X Position of this Vector.
     */
    unsigned short X;
    /**
     * \brief X Position of this Vector.
     */
    unsigned short Y;
};

#endif
