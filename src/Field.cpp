#include "Field.h"

Field::Field(unsigned short CellCount, Vector Position)
    : _CellCount(CellCount),
      _Position(Position)
{
}

Field::~Field()
{
}

const unsigned short& Field::getCellCount() const
{
    return _CellCount;
}

const Vector& Field::getPosition() const
{
    return _Position;
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

void Field::IncreaseCellCount(unsigned char &&Percentage)
{
    // TODO: Fix this calculation
    _CellCount += Percentage * (_CellCount / 100);
}


void Field::ResetActions()
{
    _Actions.Up    = 0;
    _Actions.Down  = 0;
    _Actions.Right = 0;
    _Actions.Left  = 0;
}
