#include "Bot.h"
#include <iostream>

Bot::Bot(Vector StartingPosition, TEAM Team)
    : _StartingPosition(StartingPosition),
      _Team(Team)
{
}

Bot::~Bot()
{
}

void Bot::MakeTurn(const WorldSnapshot& Snapshot)
{
    std::cout << "Making turn " << Snapshot.GetTurn() << "\n";

    for (FieldListIterator Iterator = Snapshot.GetFields(_Team).Begin();
         Iterator != Snapshot.GetFields(_Team).End();
         Iterator.Next())
    {
        Field* CurrentField = Iterator.Get();
        CurrentField->SplitCells(DIRECTION::UP, 10);
        CurrentField->SplitCells(DIRECTION::DOWN, 10);
        CurrentField->SplitCells(DIRECTION::RIGHT, 10);
        CurrentField->SplitCells(DIRECTION::LEFT, 10);
    }
}

Vector Bot::GetStartingPosition() const
{
    return _StartingPosition;
}

TEAM Bot::GetTeam() const
{
    return _Team;
}
