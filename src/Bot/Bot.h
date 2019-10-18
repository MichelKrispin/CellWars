#ifndef _BOT_H
#define _BOT_H
#include "Team.h"
#include "World/WorldSnapshot.h"
#include "World/Direction.h"
#include "World/Vector.h"

// Forward-declaration
class ConfigurationLoader;

/**
 * \brief The basic bot class.
 *
 * This class is the ground for all bots used by the world.
 */
class Bot
{
public:
    /**
     * \brief Create a new empty Bot.
     * 
     * This bot has to be initialized by the world to give it a correct starting position
     * as well as a team.
     */
    Bot();
    virtual ~Bot();

    /**
     * \brief Makes the turn for this Bot.
     * 
     * This function should be overwritten by any newly created Bot
     * as this gets called by the World on every round.
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
     * 
     * \return The team of this Bot as a TEAM enum.
     */
    virtual TEAM GetTeam() const final;
    
    /**
     * \brief Returns the team of this bot as an unsigned int.
     *
     * Normally this will only be called once on world initialization
     * to be used inside of arrays.
     * 
     * \return The team of this Bot as an index.
     */
    virtual unsigned int GetTeamAsUnsignedInt() const final;

private:
    /**
     * \brief Initializs this bot with a starting position and a given team.
     *
     * The starting position can be any direction.
     *
     * \param Direction The starting position defined as a direction.
     * \param Team The team this bot belongs to.
     * \param Configuration The configuration to be used for global variables.
     */
    void _Initialize(DIRECTION Direction, TEAM Team, ConfigurationLoader* Configuration);

    // Variables
    Vector _StartingPosition;  //< The starting position of this bot in grid indices.
    TEAM _Team;                //< The team of this bot.

    friend class World;
};

#endif
