#ifndef _UTILITIES_H
#define _UTILITIES_H

/**
 * \brief Rounds an integer and double multiplication up.
 *
 * For example:
 * If you multiplicate 10 * 0.1 you get exactly 1.
 * If you multiplicate  9 * 0.1 you get exactly 0.9 but with a cast 0.
 * This function round everything above 0.00001 up to one but not 0.0
 */
unsigned int RoundUp(const unsigned int &Base, const double &Multiplicator);

#endif
