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
 *      void MakeTurn(const WorldSnapshot& Snapshot) override
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
 *  please have a look at the Examples.h
 */
class PlayerBot : public Bot
{
public:
    /**
     * \brief Initializes the Bot with the default parameter.
     *
     * Used for normal games against another Bot.
     */
    PlayerBot();
    
    /**
     * \brief The turn function which should be overriden.
     *
     * This function will be called on every turn and will be called by the world.
     */
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override;
};

#endif
