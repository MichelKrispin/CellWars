#include "EnemyBot.h"
#include "Configuration.h"

EnemyBot::EnemyBot()
    : Bot({GRID_SIZE/4+GRID_SIZE/2, GRID_SIZE/2}, TEAM::RED)
{}

EnemyBot::~EnemyBot()
{}

void EnemyBot::MakeTurn(const WorldSnapshot& Snapshot)
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
