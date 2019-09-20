#include "Field.h"

Field::Field(unsigned short CellCount)
    : _CellCount(CellCount),
      _Position()
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
}

void Field::IncreaseCellCount(unsigned char &&Percentage)
{
    // TODO: Fix this calculation
    _CellCount += Percentage * (_CellCount / 100);
}
