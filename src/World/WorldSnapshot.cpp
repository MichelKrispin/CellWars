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

const FieldList& WorldSnapshot::GetFields() const
{
    // Using the team as an index
    return *_Fields;
}

bool WorldSnapshot::GetAdjacentFieldOf(const Field* Field, const DIRECTION &Direction) const
{
    // Calls into the Grids function and just passes everything on
    return _Grid->GetAdjacentFieldOf(_Team, Field, Direction);
}


unsigned int WorldSnapshot::GetTurn() const
{
    return _TurnNumber;
}

unsigned int WorldSnapshot::GetCount() const
{
    return _Fields->GetSize();
}

void WorldSnapshot::_Initialize(TEAM Team, FieldList* Fields, Grid* WorldGrid)
{
    _Team = Team;
    _Fields = Fields;
    _Grid = WorldGrid;
}
