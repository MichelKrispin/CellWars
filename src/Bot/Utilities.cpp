#include "Utilities.h"

unsigned int RoundUp(const unsigned int &Base, const double &Multiplicator)
{
    double Temporary = Base * Multiplicator;
    unsigned int Return = static_cast<unsigned int>(Temporary);
    if (Temporary - static_cast<double>(Return) > 10e-6)
        return Return+1;
    return Return;
}
