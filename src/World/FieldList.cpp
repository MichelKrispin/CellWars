#include "FieldList.h"

FieldList::FieldList()
{
}


FieldList::~FieldList()
{
    for (unsigned int i = 0; i < _Fields.size(); ++i)
    {
        if (_Fields[i] != nullptr)
            delete _Fields[i];
    }
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
    // TODO: Make this throw an error
    /*
    if (Index >= _Size)
        // Throw error
    */
    return _Fields[Index];
}

unsigned int FieldList::GetSize() const
{
    return _Fields.size();
}

void FieldList::_Add(Field NewField)
{
    _Fields.push_back(new Field(NewField));
}

void FieldList::_Remove(Vector &Position)
{
    // Look trough all fields and match the correponding one
    for (unsigned int i = 0; i < _Fields.size(); ++i)
    {
        Vector Copy = _Fields[i]->GetPosition();
        if (Copy == Position)
        {
            delete _Fields[i];
            _Fields.erase(_Fields.begin() + i);
            return;
        }
    }

}

