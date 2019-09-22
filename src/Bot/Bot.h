#ifndef _BOT_H
#define _BOT_H
#include "Team.h"
#include "World/WorldSnapshot.h"
#include "World/Direction.h"
#include "World/Vector.h"

/**
 * \brief The basic bot class.
 *
 * This class is the ground for all bots used by the world.
 */
class Bot
{
public:
    /**
     * \brief Initialize this bot with it starting position and a given team.
     *
     * The starting position should be somewhere between GRID_SIZE and 0 given
     * as grid indices.
     * It will be translated to pixels on world initialization.
     *
     * \param StartingPosition X and Y position in grid indices of this bot.
     * \param Team The team this bot belongs to.
     */
    Bot(Vector StartingPosition, TEAM Team);

    /**
     * \brief Initialize this bot with a default starting position and a given team.
     *
     * The starting position can be any direction.
     *
     * \param Direction The starting position defined as a direction.
     * \param Team The team this bot belongs to.
     */
    Bot(DIRECTION Direction, TEAM Team);

    virtual ~Bot();

    /**
     * \brief Makes the turn for this Bot.
     *
     * \param Snapshot A Snapshot of the world at this moment
     */
    virtual void MakeTurn(const WorldSnapshot& Snapshot);

    /**
     * \brief Returns the starting position of this bot.
     *
     * Normally this will only be called once on world initialization.
     */
    virtual Vector GetStartingPosition() const final;

    /**
     * \brief Returns the team of this bot.
     *
     * Normally this will only be called once on world initialization.
     */
    virtual TEAM GetTeam() const final;

private:
    Vector _StartingPosition;  //< The starting position of this bot in grid indices.
    const TEAM _Team;                //< The team of this bot.
};

#endif
