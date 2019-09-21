#ifndef _BOT_H
#define _BOT_H
#include <iostream>
#include "World/WorldSnapshot.h"
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
    virtual void MakeTurn(const WorldSnapshot& Snapshot);

    virtual Vector GetStartingPosition() const final;
    virtual TEAM GetTeam() const final;

private:
    const Vector _StartingPosition;
    const TEAM _Team;
};

#endif
