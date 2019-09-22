#include "WorldSnapshot.h"
#include "FieldList.h"
#include "Grid.h"

WorldSnapshot::WorldSnapshot()
    : _TurnNumber(0)
{
    // The Fields and grids are right now initialized using the friend class
    // TODO: Should be changed to be initialized by the constructor.
}

WorldSnapshot::~WorldSnapshot()
{
}

const FieldList& WorldSnapshot::GetFields(TEAM Team) const
{
    // Using the team as an index
    return _Fields[static_cast<int>(Team)];
}

bool WorldSnapshot::GetAdjacentFieldOf(const TEAM &Team, const Field* Field, const DIRECTION &Direction) const
{
    // Calls into the Grids function and just passes everything on
    return _Grid->GetAdjacentFieldOf(Team, Field, Direction);
}


unsigned int WorldSnapshot::GetTurn() const
{
    return _TurnNumber;
}

unsigned int WorldSnapshot::GetCount(const TEAM &Team) const
{
    return _Fields[static_cast<int>(Team)].GetSize();
}
