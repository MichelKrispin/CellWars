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
     * \return A constant FieldList to show which fields are currently theirs.
     */
    const FieldList &GetFields() const;

    /**
     * \brief Returns true if there is another field of the same team next to this one.
     * Returns false whenever the adjacent field is empty or possessed by another team.
     *
     * \param Field The field of which we want to know the adjacent field.
     * \param Direction The direction to look out for.
     *
     * \return Whether the adjacent field in the specified direction belongs to this fields team.
     */
    bool GetAdjacentFieldOf(const Field* Field, const DIRECTION &Direction) const;

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
     unsigned int GetCount() const;
    
private:
     // Functions
     /**
      * \brief Initialize this WorldSnapshot for the specific team.
      *
      * \param Team The team this snapshot is for.
      * \param Fields A pointer to the FieldList for fields of this team.
      * \param WorldGrid A pointer to the grid to have a global view of the world.
      */
     void _Initialize(TEAM Team, FieldList* Fields, Grid* WorldGrid);

     // Variables
     FieldList* _Fields;       //< One FieldList for each team.
     Grid* _Grid;              //< The world grid to make assumptions of adjacent fields.
     TEAM _Team;               //< The team for which is snapshot is for.
     unsigned int _TurnNumber; //< Keeping track of the current turn.

     // The world is allowed to access everything
     friend class World;
};

#endif
