#include "Field.h"
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

void Field::_IncreaseCellCount(unsigned char &&Percentage)
{
    // TODO: Fix this calculation to let it round up
    _CellCount += Percentage * (_CellCount / 100);
    if (_CellCount > MAX_COUNT_PER_FIELD)
        _CellCount = MAX_COUNT_PER_FIELD;
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

