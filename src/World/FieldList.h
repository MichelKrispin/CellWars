#ifndef _FIELDLIST_H
#define _FIELDLIST_H
#include "FieldListIterator.h"
#include "Field.h"
#include <vector>

class FieldListIterator;

/**
 * \brief Holds a list to fields.
 *
 * A field can be added and removed by its position.
 */
class FieldList
{
public:
    /*
     * \brief Initializes this FieldList to have no Fields.
     */
    FieldList();
    virtual ~FieldList();

    /**
     * \brief An iterator to iterate the FieldList.
     * \return FieldListIteraor to iterate trough all elements of this FieldList.
     */
    FieldListIterator Begin() const;

    /**
     * \brief To check whether the iterator has finished.
     * Returns an integer count for comparison.
     */
    unsigned int End() const;

    // TODO: Check for return const Field pointer
    /**
     * \brief Get the Field at the corresponding index.
     * Throws an exception if the index is out of bounds.
     *
     * \param Index The index of the field.
     * \return Returns a pointer to the field.
     */
    Field* operator[](unsigned int Index) const;


    #ifdef BUILD_PYTHON
    /**
     * \brief Returns this list as a vector.
     * 
     *  Only added if the python build is activated as the std::vector 
     *  can be converted to a native python list
     * 
     */
    const std::vector<Field*> &GetPythonList() const;
    #endif

    /**
     * \brief Get the size of the list.
     *
     * \return Returns the size of the list.
     */
    unsigned int GetSize() const;


private:
    /**
     * \brief Adding a new field to the list.
     *
     * \param NewField The new field
     */
    void _Add(Field NewField);

    /**
     * \brief Remove a field at the specified position.
     *
     * \param Position Vector of the position of the field to be removed.
     */
    void _Remove(Vector &Position);

    std::vector<Field*> _Fields; //< The actual list of fields.

    friend class World;
    friend class Grid;
};

#endif
