#include "Bot.h"
#include "World/Configuration.h"

Bot::Bot()
    : _Team(static_cast<TEAM>(-1))
{
}

Bot::~Bot() = default;

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

unsigned int Bot::GetTeamAsUnsignedInt() const
{
    return static_cast<unsigned int>(_Team);
}

void Bot::_Initialize(DIRECTION Direction, TEAM Team)
{
    _Team = Team;
    switch(Direction)
    {
        case DIRECTION::UP:
            _StartingPosition = {Configuration::Get().GridSize()/2,
                                 Configuration::Get().GridSize()/4};
            break;
        case DIRECTION::LEFT:
            _StartingPosition = {Configuration::Get().GridSize()/4,
                                 Configuration::Get().GridSize()/2};
            break;
        case DIRECTION::RIGHT:
            _StartingPosition = {Configuration::Get().GridSize()/4+Configuration::Get().GridSize()/2,
                                 Configuration::Get().GridSize()/2};
            break;
        case DIRECTION::DOWN:
            _StartingPosition = {Configuration::Get().GridSize()/2,
                                 Configuration::Get().GridSize()/4+Configuration::Get().GridSize()/2};
            break;
    }
}
