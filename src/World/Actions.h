#ifndef _ACTIONS_H
#define _ACTIONS_H

/**
 * \brief List of actions to be applied after each turn.
 *
 * Holds information of the splitting values for each field.
 */
struct Actions
{
    /** \brief Saves values for splitting upwards. */
    unsigned int Up    = 0;
    /** \brief Saves values for splitting downwards. */
    unsigned int Down  = 0;
    /** \brief Saves values for splitting to the left. */
    unsigned int Right = 0;
    /** \brief Saves values for splitting to the right. */
    unsigned int Left  = 0;
};

#endif
