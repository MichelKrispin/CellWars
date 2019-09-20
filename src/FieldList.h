#ifndef _FIELDLIST_H
#define _FIELDLIST_H
#include "Field.h"
#include "FieldListIterator.h"

class FieldListIterator;

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

    // TODO: Make this throw an error
    // TODO: Maybe return a pointer
    /**
     * \brief Get the Field at the corresponding index.
     * Throws an error if the index is out of bounds.
     *
     * \param Index The index of the field.
     * \return Returns a pointer to the field.
     */
    Field* operator[](unsigned int Index) const;

    /**
     * \brief Get the size of the list.
     *
     * \return Returns the size of the list.
     */
    unsigned int getSize() const;


private:
    /**
     * \brief Adding a new field to the list.
     *
     * \param NewField The new field
     */
    void Add(Field NewField);

    Field* _Fields;     //< The actual list of fields.
    unsigned int _Size; //< Size of the list.

    friend class World;
};

#endif
