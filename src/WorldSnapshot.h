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
    const FieldList &getFields(TEAM Team);
    
private:
    FieldList* Fields; //< One FieldList for each team.
    unsigned int TurnNumber; //< Keeping track of the current turn.
    
};

#endif
