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
    std::cout << "Making turn\n";
}

Vector Bot::getStartingPosition() const
{
    return _StartingPosition;
}

TEAM Bot::getTeam() const
{
    return _Team;
}
