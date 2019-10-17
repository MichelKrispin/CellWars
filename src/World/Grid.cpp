#include "Grid.h"
#include "FieldListIterator.h"
#include "ConfigurationLoader.h"

Grid::Grid(ConfigurationLoader* Configuration)
    : _Configuration(Configuration),
     _Size(_Configuration->GetGridSize())
{
    _Fields = new Field*[_Configuration->GetGridSize() * _Configuration->GetGridSize()];
    _SplitValues = new SplitValues[_Configuration->GetGridSize() * _Configuration->GetGridSize()];
}

Grid::~Grid()
{
    delete[] _Fields;
    delete[] _SplitValues;
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
            Vector CurrentPosition = _ConvertPixelsToGridValues(Current->GetPosition());
            _Fields[CurrentPosition.Y * _Size + CurrentPosition.X] = Current;
        }
    }

    // Initialize all SplitValues for all fields to zero
    for (unsigned int i = 0; i < _Size * _Size; ++i)
        _SplitValues[i] = {0, 0, 0, 0};
}

void Grid::SetFieldValuesAt(unsigned int x, unsigned int y, TEAM Team, unsigned int SplitValue)
{
    // Make negative or too positive values go to the opposite side of the screen
    if (static_cast<int>(x) < 0)
        x += _Configuration->GetWindowSize();
    if (static_cast<int>(x) >= _Configuration->GetWindowSize())
        x -= _Configuration->GetWindowSize();

    if (static_cast<int>(y) < 0)
        y += _Configuration->GetWindowSize();
    if (static_cast<int>(y) >= _Configuration->GetWindowSize())
        y -= _Configuration->GetWindowSize();

    Vector Position = _ConvertPixelsToGridValues({x, y});
    
    // Change the split value for each team individually at that spot
    switch (Team)
    {
        case TEAM::BLUE:
            _SplitValues[Position.Y * _Size + Position.X].Blue += SplitValue;
            break;
        case TEAM::RED:
            _SplitValues[Position.Y * _Size + Position.X].Red += SplitValue;
            break;
        case TEAM::GREEN:
            _SplitValues[Position.Y * _Size + Position.X].Green += SplitValue;
            break;
        case TEAM::YELLOW:
            _SplitValues[Position.Y * _Size + Position.X].Yellow += SplitValue;
            break;
    }
}

// Helper function to find the maximum of three values
unsigned int MaximumOfThreeValues(unsigned int v1, unsigned int v2, unsigned int v3)
{
    if (v1 >= v2 && v1 >= v3)
        return v1;
    if (v2 >= v3)
        return v2;
    return v3;
}

void Grid::ComputeAllFields(FieldList* AllFields, unsigned char NumberOfTeams)
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
            if (!CurrentSplitValues.Blue  && !CurrentSplitValues.Red &&
                !CurrentSplitValues.Green && !CurrentSplitValues.Yellow)
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
                    case TEAM::GREEN:
                        CurrentSplitValues.Green += CurrentField->GetCellCount();
                        break;
                    case TEAM::YELLOW:
                        CurrentSplitValues.Yellow += CurrentField->GetCellCount();
                        break;
                }
            }

            // TODO: Find something more elegant to solve this
            // Calculate who wins this spot (Has the most cells split in this direction)
            // Indicator for the fields winner and the difference which will stay there
            char FieldGoesTo = -1;
            unsigned int  CellDifference = 0;
            if (CurrentSplitValues.Blue > CurrentSplitValues.Red   && // Only wins if it is the greatest
                CurrentSplitValues.Blue > CurrentSplitValues.Green &&
                CurrentSplitValues.Blue > CurrentSplitValues.Yellow)
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::BLUE); // 0
                CellDifference = CurrentSplitValues.Blue -
                        MaximumOfThreeValues(CurrentSplitValues[1], CurrentSplitValues[2], CurrentSplitValues[3]);
            }
            else if (CurrentSplitValues.Red > CurrentSplitValues.Blue  &&
                     CurrentSplitValues.Red > CurrentSplitValues.Green &&
                     CurrentSplitValues.Red > CurrentSplitValues.Yellow)
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::RED); // 1
                CellDifference = CurrentSplitValues.Red -
                        MaximumOfThreeValues(CurrentSplitValues[0], CurrentSplitValues[2], CurrentSplitValues[3]);
            }
            else if (CurrentSplitValues.Green > CurrentSplitValues.Blue &&
                     CurrentSplitValues.Green > CurrentSplitValues.Red  &&
                     CurrentSplitValues.Green > CurrentSplitValues.Yellow)
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::GREEN); // 2
                CellDifference = CurrentSplitValues.Green -
                        MaximumOfThreeValues(CurrentSplitValues[0], CurrentSplitValues[1], CurrentSplitValues[3]);
            }
            else if (CurrentSplitValues.Yellow > CurrentSplitValues.Blue &&
                     CurrentSplitValues.Yellow > CurrentSplitValues.Red  &&
                     CurrentSplitValues.Yellow > CurrentSplitValues.Green)
            {
                FieldGoesTo = static_cast<unsigned int>(TEAM::YELLOW); // 3
                CellDifference = CurrentSplitValues.Yellow -
                        MaximumOfThreeValues(CurrentSplitValues[0], CurrentSplitValues[1], CurrentSplitValues[2]);
            }

            // If the difference of both cells is above the max take the max
            // (For whatever reason can this be achieved?)
            if (CellDifference > _Configuration->GetMaxCountPerField())
                CellDifference = _Configuration->GetMaxCountPerField();

            // If FieldGoesTo is still -1 and there wasn't a field already there is no need to do anything
            if (FieldAlreadyExists == -1 && FieldGoesTo == -1)
            {
                CurrentSplitValues.Reset(); // Reset split values for this spot afterwards
                continue;
            }

            // Save the starting position for the field in pixel values
            Vector StartingPosition(x, y);
            StartingPosition.X *= _Configuration->GetWindowSize() / _Configuration->GetGridSize();
            StartingPosition.Y *= _Configuration->GetWindowSize() / _Configuration->GetGridSize();

            // If the field doesn't go to but exists already it should be deleted
            if (FieldGoesTo == -1)
            {
                AllFields[static_cast<unsigned int>(CurrentField->GetTeam())]
                    ._Remove(StartingPosition);
                continue;
            }

            // If there is no field but the field has a winner a new Field has to be created at this spot
            if (FieldAlreadyExists == -1)
            {
                // Add a new field to the correct array of all fields
                // which is an array of team count length
                AllFields[static_cast<unsigned int>(FieldGoesTo)]
                    ._Add(Field(_Configuration, static_cast<TEAM>(FieldGoesTo), CellDifference, StartingPosition));
                CurrentSplitValues.Reset(); // Reset split values for this spot afterwards
                continue;
            }

            // If otherwise the existing field at this spot is of the same team
            // as the winning team here decrease its cells count
            if (FieldAlreadyExists == FieldGoesTo)
            {
                CurrentField->_SetCellCount(CellDifference);
                CurrentSplitValues.Reset(); // Reset split values for this spot afterwards
                continue;
            }
                    
            // If the other team is winning over the owner of this field
            // remove it from their list and create a new one
            AllFields[static_cast<unsigned int>(CurrentField->GetTeam())]
                ._Remove(StartingPosition);

            AllFields[static_cast<unsigned int>(FieldGoesTo)]
                ._Add(Field(_Configuration, static_cast<TEAM>(FieldGoesTo), CellDifference, StartingPosition));

            CurrentSplitValues.Reset(); // Reset split values for this spot afterwards
        }
    }
    _UpdateAllReferences(AllFields, NumberOfTeams);
}

bool Grid::GetAdjacentFieldOf(const TEAM &Team, const Field* Field, const DIRECTION &Direction) const
{
    // First get its position in grid values
    Vector Position = _ConvertPixelsToGridValues(Field->GetPosition());
    switch (Direction)
    {
        case DIRECTION::UP:
            Position.Y -= 1;
            break;
        case DIRECTION::DOWN:
            Position.Y += 1;
            break;
        case DIRECTION::RIGHT:
            Position.X += 1;
            break;
        case DIRECTION::LEFT:
            Position.X -= 1;
            break;
    }
   
    // Same goes after going one step aside but in grid space
    if (static_cast<short>(Position.X) < 0)
        Position.X += _Configuration->GetGridSize();
    if (static_cast<short>(Position.X) >= _Configuration->GetGridSize())
        Position.X -= _Configuration->GetGridSize();

    if (static_cast<short>(Position.Y) < 0)
        Position.Y += _Configuration->GetGridSize();
    if (static_cast<short>(Position.Y) >= _Configuration->GetGridSize())
        Position.Y -= _Configuration->GetGridSize();

    // If a nullptr is at the new position return false
    // Or if their team doesn't equal (short circuiting)
    return !(_Fields[Position.Y * _Size + Position.X] == nullptr ||
             _Fields[Position.Y * _Size + Position.X]->GetTeam() != Team);
}

// TODO: Remove this function as GetPositionAsGrid exists inside of the Field class
Vector Grid::_ConvertPixelsToGridValues(const Vector &InputPosition) const
{
    return {
        static_cast<unsigned int>(InputPosition.X * _Configuration->GetGridSize() / _Configuration->GetWindowSize()),
        static_cast<unsigned int>(InputPosition.Y * _Configuration->GetGridSize() / _Configuration->GetWindowSize())
    };
}

void Grid::_UpdateAllReferences(FieldList* FieldsList, const unsigned char &NumberOfTeams)
{
    // TODO: This whole function can probably be more efficient or even removed
    // Reset all of them so there is no need to be scared of removed fields
    for (unsigned int i = 0; i < _Size * _Size; ++i)
        _Fields[i] = nullptr;

    // Then add the Fields of the FieldsList our list
    for (unsigned char i = 0; i < NumberOfTeams; ++i)
    {
        for (FieldListIterator it = FieldsList[i].Begin();
             it != FieldsList[i].End();
             it.Next())
        {
            Field* Current = it.Get();
            Vector CurrentPosition = _ConvertPixelsToGridValues(Current->GetPosition());
            _Fields[CurrentPosition.Y * _Size + CurrentPosition.X] = Current;
        }
    }
}
