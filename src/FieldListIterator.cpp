#include "FieldListIterator.h"

FieldListIterator::FieldListIterator()
{
}

FieldListIterator::FieldListIterator(const FieldList* List)
    : _ConnectedList(List),
      _Count(0)
{
}

FieldListIterator::~FieldListIterator()
{
}


bool FieldListIterator::operator!=(unsigned int other)
{
    return other != _Count;
}

void FieldListIterator::operator++(int)
{
    Next();
}

void FieldListIterator::Next()
{
    _Count++;
}

Field* FieldListIterator::Get()
{
    return _ConnectedList[0][_Count];
}
