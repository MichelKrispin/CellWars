#ifndef _WORLDSNAPSHOT_H
#define _WORLDSNAPSHOT_H
#include "FieldList.h"
#include "Team.h"

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
     * \brief Returns the actual turn count starting at
     *
     * \return The count of turns.
     */
     unsigned int GetTurn() const;
    
private:
    FieldList* Fields; //< One FieldList for each team.
    unsigned int _TurnNumber; //< Keeping track of the current turn.

    // The world is allowed to access everything
    friend class World;
};

#endif
