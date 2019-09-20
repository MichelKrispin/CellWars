#include "FieldList.h"

FieldList::FieldList()
    : _Size(0)
{
    _Fields = nullptr;
}


FieldList::~FieldList()
{
}

FieldListIterator FieldList::Begin() const
{
    return FieldListIterator(this);
}

unsigned int FieldList::End() const
{
    return _Size;
}

Field* FieldList::operator[](unsigned int Index) const
{
    /*
    if (Index >= _Size)
        // Throw error
    */
    return _Fields+Index;
}

