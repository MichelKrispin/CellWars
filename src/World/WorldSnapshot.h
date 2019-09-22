#ifndef _WORLDSNAPSHOT_H
#define _WORLDSNAPSHOT_H
#include "Bot/Team.h"
#include "World/Direction.h"

class Grid;
class FieldList;
class Field;

/**
 * \brief Used to pass a snapshot of the world to the bots.
 *
 * The world snapshot keeps track of everything which is needed by the bots.
 */
class WorldSnapshot
{
public:
    /**
     * \brief Creates a new snapshot of the world.
     */
    WorldSnapshot();
    ~WorldSnapshot();
    
    /**
     * \brief Returns the FieldList of the specific team.
     * The Team parameter will be used as an index for the FieldList array hold by this snapshot.
     *
     * \param Team The team which wants to know about its fields.
     * \return A constant FieldList to show which fields are currently theirs.
     */
    const FieldList &GetFields(TEAM Team) const;

    /**
     * \brief Returns true if there is another field of the same team next to this one.
     * Returns false whenever the adjacent field is empty or possessed by another team.
     *
     * \param Direction The direction to look out for.
     *
     * \return Whether the adjacent field in the specified direction belongs to this fields team.
     */
    bool GetAdjacentFieldOf(const TEAM &Team, const Field* Field, const DIRECTION &Direction) const;

    /**
     * \brief Returns the actual turn count starting at
     *
     * \return The count of turns.
     */
     unsigned int GetTurn() const;

     /**
      * \brief Returns the number of cells on the field for this team.
      *
      * \return Number of cells.
      */
     unsigned int GetCount(const TEAM &Team) const;
    
private:
    FieldList* _Fields;        //< One FieldList for each team.
    Grid* _Grid;               //< The world grid to make assumptions of adjacent fields.
    unsigned int _TurnNumber; //< Keeping track of the current turn.

    // The world is allowed to access everything
    friend class World;
};

#endif
