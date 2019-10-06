#include "PlayerBot.h"
#include "Configuration.h"
#include "World/FieldList.h"

PlayerBot::PlayerBot()
//    : Bot({GRID_SIZE/4, GRID_SIZE/2}, TEAM::BLUE)
    : Bot()
{}

PlayerBot::PlayerBot(DIRECTION Direction, TEAM Team)
    : Bot(Direction, Team)
{
}

PlayerBot::~PlayerBot()
{}

void PlayerBot::MakeTurn(const WorldSnapshot& Snapshot)
{
    for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
         Iterator != Snapshot.GetFields().End();
         Iterator.Next())
    {
        Field* CurrentField = Iterator.Get();
        CurrentField->SplitCells(DIRECTION::UP, CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::DOWN, CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::LEFT, CurrentField->GetCellCount() * 0.1);
    }
}
