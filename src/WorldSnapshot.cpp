#include "WorldSnapshot.h"

WorldSnapshot::WorldSnapshot()
    : _TurnNumber(0)
{
}

WorldSnapshot::~WorldSnapshot()
{
}

const FieldList& WorldSnapshot::GetFields(TEAM Team) const
{
    // Using the team as an index
    return Fields[static_cast<int>(Team)];
}

unsigned int WorldSnapshot::GetTurn() const
{
    return _TurnNumber;
}
