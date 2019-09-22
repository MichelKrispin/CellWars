#ifndef _PLAYERBOT_H
#define _PLAYERBOT_H
#include "Bot/Bot.h"

/**
 * \brief A basic player bot class which can be easily extended.
 *
 * This class should be the starting point for any new player class.
 * To create your own Bot inherit from this class and overwrite 
 * the MakeTurn function.
 * \code {.cpp}
 *  class MyBot : public PlayerBot
 *  {
 *      virtual void MakeTurn(const WorldSnapshot& Snapshot) override
 *      {
 *          // Iterate trough every of your fields
 *          for (FieldListIterator Iterator = Snapshot.GetFields(GetTeam()).Begin();
 *               Iterator != Snapshot.GetFields(GetTeam()).End();
 *               Iterator.Next())
 *          {
 *              // Get the current field of the iterator
 *              Field* CurrentField = Iterator.Get();
 *              // Split the cells of this field in a specific direction
 *              CurrentField->SplitCells(DIRECTION::UP, 10);
 *          }
 *      }
 *  };
 * \endcode
 *
 *  If you want to let one PlayerBot play against another PlayerBot
 *  you can call the World Play function just like before.
 */
class PlayerBot : public Bot
{
public:
    /**
     * \brief Initializes the Bot with the default parameter.
     *
     * Used for normal games against an EnemyBot.
     */
    PlayerBot();

    /**
     * \brief Initializes the Bot with a custom TEAM.
     *
     * To be used to let one PlayerBot play against another PlayerBot.
     * If used both player have to have unique teams.
     * 
     * \param Direction The position of the starting position.
     * \param Team The team this player belongs to. (One of the teams from Teams.h)
     */
    PlayerBot(DIRECTION Direction, TEAM Team);
    virtual ~PlayerBot();
    
    /**
     * \brief The turn function which should be overriden.
     *
     * This function will be called on every turn and will be called by the world.
     */
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override;
};

#endif
