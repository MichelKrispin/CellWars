#include "Bot.h"

Bot::Bot(Vector StartingPosition, TEAM Team)
    : _StartingPosition(StartingPosition),
      _Team(Team)
{
}

Bot::~Bot()
{
}

void Bot::MakeTurn(const WorldSnapshot& Snapshot)
{}

Vector Bot::GetStartingPosition() const
{
    return _StartingPosition;
}

TEAM Bot::GetTeam() const
{
    return _Team;
}
