#ifndef _GRID_H
#define _GRID_H
#include "Field.h"
#include "Bot/Team.h"
#include "FieldList.h"

// Forward declaration
class Configuration;

// TODO: Outsource this to its own file
/**
 * \brief A struct just to keep track of how many cells are added to a field.
 *
 * Might be removed in the future.
 */
struct SplitValues
{
    /** \brief The splitted cells by the blue team. */
    unsigned int Blue;
    /** \brief The splitted cells by the red team. */
    unsigned int Red;
    /** \brief The splitted cells by the green team. */
    unsigned int Green;
    /** \brief The splitted cells by the yellow team. */
    unsigned int Yellow;

    /** \brief Reset all values. */
    void Reset()
    {
        Blue   = 0;
        Red    = 0;
        Green  = 0;
        Yellow = 0;
    }

    unsigned int operator[] (unsigned char index)
    {
        switch (index)
        {
            case 0:
                return Blue;
            case 1:
                return Red;
            case 2:
                return Green;
            case 3:
                return Yellow;
            default:
                return -1;
        }
    }
};

/**
 * \brief Keeps track of all fields in another way.
 *
 * While the bots keep track of their fields with a list this
     * class uses another representation to make some calculations easier.
 */
class Grid
{
public:
    /**
     * \brief Create an empty grid.
     * Even if its empty it has array fields for all of the grid.
     * 
     * \param Configuration The adress of the configuration which is loaded once.
     */
    Grid();
    virtual ~Grid();

    /**
     * \brief Initialize the grid with  all existing fields.
     *
     * \param FieldsList The FieldList array of all fields hold by the world.
     * \param FieldsSize The length of the FieldList array.
     */
    void Initialize(FieldList* FieldsList, unsigned int FieldsSize);

    /**
     * \brief Setting the addition values at any position of the field.
     * Used by the world to set the values of the splitted cells.
     *
     * \param x The x position in pixel values.
     * \param y The y position in pixel values.
     * \param Team The team member for which the field values will be set.
     * \param SplitValue How many cells will be split to this field.
     */
    void SetFieldValuesAt(unsigned int x, unsigned int y, TEAM Team, unsigned int SplitValue);

    /**
     * \brief Returns true if there is another field of the same team next to this one.
     * Returns false whenever the adjacent field is empty or possessed by another team.
     * Used by the WorldSnapshot to allow a Bot to look next to its fields.
     *
     * \param Team The team to which the field belongs to.
     * \param Field The field for which the adjacent fields are searched for.
     * \param Direction The direction to look out for.
     *
     * \return Whether the adjacent field in the specified direction belongs to this fields team.
     */
   bool GetAdjacentFieldOf(const TEAM &Team, const Field* Field, const DIRECTION &Direction) const;

    /**
     * \brief Computes all fields in the grid.
     * Calculates the difference between the fields and check whether new fields should be added
     * or some should be removed.
     *
     * \param AllFields Can be modified if new fields are created or if fields are removed for a team.
     * \param NumberOfTeams How many team are playing.
     */
    void ComputeAllFields(FieldList* AllFields, unsigned char NumberOfTeams);

private:
    // Functions
    /**
     * \brief Converts pixel values to positions which lie on the grid.
     *
     * \param InputPosition The input position in pixels.
     * \return Returns a converted Vector bound to GRID_SIZE.
     */
    Vector _ConvertPixelsToGridValues(const Vector& InputPosition) const;

    /**
     * \brief Updates all the field references from the orginal list.
     *
     * \param FieldsList The FieldList array of all fields hold by the world.
     * \param NumberOfTeams The number of teams currently playing.
     */
    void _UpdateAllReferences(FieldList* FieldsList, const unsigned char &NumberOfTeams);

    // Variables
    Field** _Fields; //< Pointer to all fields. Initialized all with nullptr
    SplitValues* _SplitValues; //< Keeping track of each teams splitted values 
    const unsigned int _Size; //< Saving the size/width of the grid

};

#endif
