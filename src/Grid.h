#ifndef _GRID_H
#define _GRID_H
#include "Configuration.h"
#include "Field.h"
#include "Team.h"
#include "FieldList.h"

struct SplitValues
{
    unsigned int Blue;
    unsigned int Red;
};

class Grid
{
public:
    /**
     * \brief Create an empty grid.
     * Even if its empty it has array fields for all of the grid.
     */
    Grid();
    virtual ~Grid();

    /**
     * \brief Initialize the grid with  all existing fields.
     *
     * \param FieldsList The FieldList array of all fields hold by the world.
     * \param Size The length of the FieldList array.
     */
    void Initialize(FieldList* FieldsList, unsigned int FieldsSize);

    /**
     * \brief Setting the addition values at any position of the field.
     * Used by the world to set the values of the splitted cells.
     *
     * \param x The x position in grid values.
     * \param y The y position in grid values.
     */
    void SetFieldValuesAt(unsigned int x, unsigned int y, TEAM Team, unsigned int SplitValue);

    /**
     * \brief Computes all fields in the grid.
     * Calculates the difference between the fields and check whether new fields should be added
     * or some should be removed.
     *
     * \param AllFields Can be modified if new fields are created or if fields are removed for a team.
     */
    void ComputeAllFields(FieldList* AllFields);

private:
    // Functions
    // TODO: Check if needed
    /**
     * \brief Converts pixel values to positions which lie on the grid.
     *
     * \param InputPosition The input position in pixels.
     * \return Returns a converted Vector bound to GRID_SIZE.
     */
    Vector _ConvertPixelsToGridValues(Vector InputPosition);

    /**
     * \brief Updates all the field references from the orginal list.
     *
     * \param FieldsList The FieldList array of all fields hold by the world.
     */
    void _UpdateAllReferences(FieldList* FieldsList);

    // Variables
    Field* _Fields[GRID_SIZE * GRID_SIZE]; //< Pointer to all fields. Initialized all with nullptr
    // TODO: Make this more adjustable for multiple teams (dynamic sized array like _Fields of World)
    SplitValues _SplitValues[GRID_SIZE * GRID_SIZE]; //< Keeping track of each teams splitted values 
    // TODO: Maybe add array to keep track of fields team
    const unsigned int _Size; //< Saving the size/width of the grid

};

#endif
