#ifndef _FIELD_H
#define _FIELD_H
#include "Direction.h"
#include "Vector.h"
#include "Actions.h"
#include "Bot/Team.h"

class Field
{
public:
    /**
     * \brief Creates a new field which will the default value of 1 cell.
     *
     * \param Team The team this field belongs to.
     * \param CellCount The count with which this field will be initialized.
     * \param Position The position of this field in the grid
     */
    Field(TEAM Team, unsigned short CellCount = 1, Vector Position = {0, 0});
    virtual ~Field();

    /**
     * \brief Returns the cell count of this field.
     * This cell count will be between 1 and MAX_COUNT_PER_FIELD (100 by default).
     * If the cell count is below 1 it will be deleted.
     *
     * \return Cell count as an unsigned short.
     */
    const unsigned short& GetCellCount() const;

    /**
     * \brief Returns the position of this field.
     * The position is defined on the grid.
     * \return A 2D Vector with X and Y positions.
     */
    const Vector &GetPosition() const;

    // TODO: Raise an exception if the input cell count is above existing cells
    /**
     * \brief Splits the CellCount to the given direction.
     * Splits the number of CellCount cells to given direction.
     * Can be done in all directions. If specified twice for one direction
     * the previous split will be overriden.
     *
     * \param Direction The direction of this split.
     * \param CellCount Number of cells to be split to the right.
     */
    void SplitCells(DIRECTION Direction, unsigned short CellCount);

    /**
     * \brief Returns the team this field belongs to
     *
     * \return A TEAM enum to indicate the team.
     */
    const TEAM &GetTeam() const;

private:
    // Functions
    /**
     * \brief Increases the cell count by the percentage given as input.
     * Used by the World to increase this fields cells after each turn.
     * The added cells will be rounded up.
     *
     * \param Percentage The percentage by which the count will be increased.
     */
    void _IncreaseCellCount(unsigned char &&Percentage);

    /**
     * \brief Resets the Actions struct.
     * Used after all actions have been executed.
     */
    void _ResetActions();

    /**
     * \brief Sets the cell count of this field to the specified value.
     *
     * \param NewCellCount The new cell count which will replace the old value.
     */
    void _SetCellCount(unsigned int NewCellCount);

    // Variables
    TEAM _Team; //< The team to which this field belongs
    unsigned short _CellCount; //< The cell count of this field.
    Vector _Position; //< The position of this field.
    Actions _Actions; //< A list of actions which will be used by the World to update the fields

    // The world has access to everything.
    friend class World;
    friend class Grid; // And it seems like the Grid has too...
};

#endif
