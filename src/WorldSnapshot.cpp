#include "WorldSnapshot.h"

WorldSnapshot::WorldSnapshot()
{
}

WorldSnapshot::~WorldSnapshot()
{
}

const FieldList& WorldSnapshot::getFields(TEAM Team)
{
    // Using the team as an index
    return Fields[static_cast<int>(Team)];
}
