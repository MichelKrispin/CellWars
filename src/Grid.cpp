#include "Grid.h"
#include "FieldListIterator.h"

Grid::Grid()
    : _Size(GRID_SIZE)
{
}

Grid::~Grid()
{
}

void Grid::Initialize(FieldList* FieldsList, unsigned int FieldsSize)
{
    // Initialize all Field pointers to a nullptr
    // Size could also be used in two loops to be a unique identifier 
    for (unsigned int i = 0; i < _Size * _Size; ++i)
        _Fields[i] = nullptr;

    // Then add the Fields of the FieldsList our list
    for (unsigned int i = 0; i < FieldsSize; ++i)
    {
        for (FieldListIterator it = FieldsList[i].Begin();
             it != FieldsList[i].End();
             it.Next())
        {
            Field* Current = it.Get();
            Vector CurrentPosition = ConvertPixelsToGridValues(Current->GetPosition());
            _Fields[CurrentPosition.Y * _Size + CurrentPosition.X] = Current;
        }
    }

    // Initialize all SplitValues for all fields to zero
    for (unsigned int i = 0; i < _Size * _Size; ++i)
        _SplitValues[i] = {0, 0};
}

void Grid::SetFieldValuesAt(unsigned int x, unsigned int y, TEAM Team, unsigned int SplitValue)
{
    Vector Position = ConvertPixelsToGridValues({x, y});
    
    // Make negativ values go to the opposite side of the screen
    if (Position.X < 0)
        Position.X += GRID_SIZE;
    if (Position.Y < 0)
        Position.Y += GRID_SIZE;

    // Change the split value for each team individually at that spot
    switch (Team)
    {
        case TEAM::BLUE:
            _SplitValues[Position.Y * _Size + Position.X].Blue = SplitValue;
            break;
        case TEAM::RED:
            _SplitValues[Position.Y * _Size + Position.X].Red = SplitValue;
            break;
    }
}

void Grid::ComputeAllFields(FieldList* AllFields)
{
    // Loop trough all fields
    for (unsigned int y = 0; y < _Size; ++y)
    {
        for (unsigned int x = 0; x < _Size; ++x)
        {
            // Temporary alias/reference to make code more readable
            SplitValues &CurrentSplitValues = _SplitValues[y * _Size + x];
            Field*       CurrentField       = _Fields[y * _Size + x];
            // Check if there are any split values so that the field at this position changes
            if (!CurrentSplitValues.Blue && !CurrentSplitValues.Red)
                continue;
            
            // So at least one is non zero
            // Indicator if there is already a field on this spot
            // If it exists it will be equal to the number of the TEAM enum
            char FieldAlreadyExists = -1;
            // Check for a field
            if (CurrentField != nullptr)
            {
                FieldAlreadyExists = static_cast<unsigned int>(CurrentField->GetTeam());
                // Add the already existing cells to the split value for calculation
                switch (CurrentField->GetTeam())
                {
                    case TEAM::BLUE:
                        CurrentSplitValues.Blue += CurrentField->GetCellCount();
                        break;
                    case TEAM::RED:
                        CurrentSplitValues.Red += CurrentField->GetCellCount();
                        break;
                }
            }


            // Indicator for the fields winner and the difference which will stay there
            char FieldGoesTo = -1;
            unsigned int  CellDifference = 0;
            if (CurrentSplitValues.Blue > CurrentSplitValues.Red)
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::BLUE); // 0
                CellDifference = CurrentSplitValues.Blue - CurrentSplitValues.Red;
            }
            else
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::RED); // 1
                CellDifference = CurrentSplitValues.Blue - CurrentSplitValues.Red;
            }

            // If FieldGoesTo is still 0 and there wasn't a field already there is no need to do anything
            if (FieldAlreadyExists == -1 && FieldGoesTo == -1)
            {
                CurrentSplitValues.Blue = 0; // Reset split values for this spot afterwards
                CurrentSplitValues.Red  = 0;
                continue;
            }

            // Save the starting position for the field in pixel values
            Vector StartingPosition(x, y);
            StartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
            StartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;

            // If there is no field but the field has a winner a new Field has to be created at this spot
            if (FieldAlreadyExists == -1)
            {
                // Add a new field to the correct array of all fields
                // which is an array of team count length
                AllFields[static_cast<unsigned int>(FieldGoesTo)]
                    ._Add(Field(static_cast<TEAM>(FieldGoesTo), CellDifference, StartingPosition));
                CurrentSplitValues.Blue = 0; // Reset split values for this spot afterwards
                CurrentSplitValues.Red  = 0;
                continue;
            }

            // If otherwise the existing field at this spot is of the same team
            // as the winning team here decrease its cells count
            if (FieldAlreadyExists == FieldGoesTo)
            {
                CurrentField->_SetCellCount(CellDifference);
                CurrentSplitValues.Blue = 0; // Reset split values for this spot afterwards
                CurrentSplitValues.Red  = 0;
                continue;
            }
                    
            // If the other team is winning over the owner of this field remove it from their list
            // and create a new one
            AllFields[FieldGoesTo ? 0 : 1] // Remove it from the opposite ones list
                ._Remove(StartingPosition); 
            AllFields[static_cast<unsigned int>(FieldGoesTo)] // Add to the winner one
                ._Add(Field(static_cast<TEAM>(FieldGoesTo), CellDifference, StartingPosition));
        }
    }
}

Vector Grid::ConvertPixelsToGridValues(Vector InputPosition)
{
    /*
    return {
        static_cast<unsigned int>(InputPosition.X - (InputPosition.X % GRID_SIZE)),
        static_cast<unsigned int>(InputPosition.X - (InputPosition.X % GRID_SIZE))
    };
    */
    return {
        static_cast<unsigned int>(InputPosition.X * GRID_SIZE / WINDOW_SIZE),
        static_cast<unsigned int>(InputPosition.Y * GRID_SIZE / WINDOW_SIZE)
    };
}

