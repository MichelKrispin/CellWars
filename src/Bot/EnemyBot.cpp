#include "EnemyBot.h"
#include "Configuration.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"

EnemyBot::EnemyBot()
    : Bot({GRID_SIZE/4+GRID_SIZE/2, GRID_SIZE/2}, TEAM::RED)
{}

EnemyBot::~EnemyBot()
{}

void EnemyBot::MakeTurn(const WorldSnapshot& Snapshot)
{
    for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
         Iterator != Snapshot.GetFields().End();
         Iterator.Next())
    {
        Field* CurrentField = Iterator.Get();
        CurrentField->SplitCells(DIRECTION::UP,    CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::DOWN,  CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount() * 0.1);
        CurrentField->SplitCells(DIRECTION::LEFT,  CurrentField->GetCellCount() * 0.1);
    }
}
