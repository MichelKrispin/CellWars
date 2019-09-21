#include "PlayerBot.h"
#include "Configuration.h"

PlayerBot::PlayerBot()
    : Bot({GRID_SIZE/4, GRID_SIZE/2}, TEAM::BLUE)
{}

PlayerBot::~PlayerBot()
{}

void PlayerBot::MakeTurn(const WorldSnapshot& Snapshot)
{
    for (FieldListIterator Iterator = Snapshot.GetFields(GetTeam()).Begin();
         Iterator != Snapshot.GetFields(GetTeam()).End();
         Iterator.Next())
    {
        Field* CurrentField = Iterator.Get();
        CurrentField->SplitCells(DIRECTION::UP, 10);
        CurrentField->SplitCells(DIRECTION::DOWN, 10);
        CurrentField->SplitCells(DIRECTION::RIGHT, 10);
        CurrentField->SplitCells(DIRECTION::LEFT, 10);
    }
}
