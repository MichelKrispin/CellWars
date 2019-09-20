#ifndef _BOT_H
#define _BOT_H
#include <iostream>
#include "WorldSnapshot.h"

class Bot
{
public:
    Bot();
    ~Bot();

    /**
     * \brief Makes the turn for this Bot.
     *
     * \param Snapshot A Snapshot of the world at this moment
     */
    void MakeTurn(const WorldSnapshot& Snapshot);

private:

};

#endif
