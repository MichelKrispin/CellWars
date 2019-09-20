#ifndef _BOT_H
#define _BOT_H
#include <iostream>
#include "WorldSnapshot.h"
#include "Team.h"

class Bot
{
public:
    // TODO: Make this better for inheritance
    Bot(Vector StartingPosition, TEAM Team);
    virtual ~Bot();

    /**
     * \brief Makes the turn for this Bot.
     *
     * \param Snapshot A Snapshot of the world at this moment
     */
    void MakeTurn(const WorldSnapshot& Snapshot);

    Vector getStartingPosition() const;
    TEAM getTeam() const;

private:
    Vector _StartingPosition;
    TEAM _Team;
};

#endif
