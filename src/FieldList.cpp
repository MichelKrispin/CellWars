#include "FieldList.h"

FieldList::FieldList()
{
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
    return _Fields.size();
}

Field* FieldList::operator[](unsigned int Index) const
{
    /*
    if (Index >= _Size)
        // Throw error
    */
    return _Fields[Index];
}

unsigned int FieldList::getSize() const
{
    return _Fields.size();
}

void FieldList::_Add(Field NewField)
{
    _Fields.push_back(NewField);
}

void FieldList::_Remove(Vector Position)
{
    // Look trough all fields and match the correponding one
    for (unsigned int i = 0; i < _Fields.size(); ++i)
    {
        if (_Fields[i].GetPostion() == Position)
        {
            _Fields.erase(_Fields.begin() + i);
            return;
        }
    }

}

