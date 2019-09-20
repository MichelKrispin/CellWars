#include "FieldList.h"

FieldList::FieldList()
    : _Size(0)
{
    _Fields = nullptr;
}


FieldList::~FieldList()
{
    delete[] _Fields;
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

unsigned int FieldList::getSize() const
{
    return _Size;
}

void FieldList::Add(Field NewField)
{
    _Size++;
    // TODO: Make this cleaner. Maybe use std::vector
    if (_Fields == nullptr)
    {
        _Fields = new Field(NewField);
        _Size++;
        return;
    }
    
    Field* tmp = _Fields;
    _Fields = new Field[_Size];
    for (unsigned int i = 0; i < _Size-1; ++i)
        _Fields[i] = tmp[i];

    _Fields[_Size-1] = NewField;
}

