#include "Field.h"
#include "Bot/Utilities.h"
#include "Configuration.h"

Field::Field(TEAM Team, unsigned short CellCount, Vector Position)
    : _Team(Team),
      _CellCount(CellCount),
      _Position(Position)
{
}

Field::~Field()
{
}

const unsigned short& Field::GetCellCount() const
{
    return _CellCount;
}

const Vector& Field::GetPosition() const
{
    return _Position;
}

Vector Field::GetPositionAsGrid() const
{
    return {
        static_cast<unsigned int>(_Position.X * Configuration::Get().GridSize() / Configuration::Get().WindowSize()),
        static_cast<unsigned int>(_Position.Y * Configuration::Get().GridSize() / Configuration::Get().WindowSize())
    };
}

const TEAM& Field::GetTeam() const
{
    return _Team;
}

void Field::SplitCells(DIRECTION Direction, unsigned short CellCount)
{
    switch(Direction)
    {
        case DIRECTION::UP:
            _Actions.Up    = CellCount;
            break;
        case DIRECTION::DOWN:
            _Actions.Down  = CellCount;
            break;
        case DIRECTION::RIGHT:
            _Actions.Right = CellCount;
            break;
        case DIRECTION::LEFT:
            _Actions.Left  = CellCount;
            break;
    }
}

void Field::SplitCellsAllDirections(unsigned short CellCount)
{
    _Actions.Up    = CellCount;
    _Actions.Down  = CellCount;
    _Actions.Right = CellCount;
    _Actions.Left  = CellCount;
}

void Field::_IncreaseCellCount(const double &Percentage)
{
    _CellCount += RoundUp(_CellCount, Percentage);
    if (_CellCount > Configuration::Get().MaxCountPerField())
        _CellCount = Configuration::Get().MaxCountPerField();
}


void Field::_ResetActions()
{
    _Actions.Up    = 0;
    _Actions.Down  = 0;
    _Actions.Right = 0;
    _Actions.Left  = 0;
}

void Field::_SetCellCount(unsigned int NewCellCount)
{
    _CellCount = NewCellCount;
}

