#include "FieldList.h"
#include <exception>

// This class is only for throwing the exception at the right spot
class OutOfBoundsException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Tried to access out of bounds index";
    }
};

FieldList::FieldList() = default;


FieldList::~FieldList()
{
    for (auto &_Field : _Fields)
        delete _Field;
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
    if (Index >= _Fields.size())
        throw OutOfBoundsException();
    return _Fields[Index];
}

#ifdef BUILD_PYTHON
std::vector<Field*> FieldList::GetPythonList() const
{
    return _Fields;
}
#endif

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

