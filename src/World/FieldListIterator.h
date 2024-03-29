#ifndef _FIELDLISTITERATOR_H
#define _FIELDLISTITERATOR_H
#include "Field.h"

class FieldList;

/**
 * \brief An iterator for the FieldList.
 *
 * Makes it easy to iterate over every field in the list.
 */
class FieldListIterator
{
public:
    /**
     * \brief Initializes an empty iterator.
     */
    FieldListIterator();

    /**
     * \brief Initializes the iterator with a connected list.
     */
    FieldListIterator(const FieldList* List);
    virtual ~FieldListIterator();

    /**
     * \brief Overwrites the behaviour of the default unequal operator.
     * Used to use this iterator inside a for loop.
     *
     * \param other Other The size for comparison.
     */
    bool operator!=(unsigned int other);

    /**
     * \brief Overwrite the behaviour of the default ++ operator.
     * Go to the next element.
     */
    void operator++(int);

    /**
     * \brief Get the current element.
     */
    Field* Get();

    /**
     * \brief Go to the next element.
     */
    void Next();

private:
    const FieldList* _ConnectedList; //< Connected FieldList.
    unsigned int _Count; //< Count the times of iteration up.

};

#endif
