#include "Bot/PlayerBot.h"
#include "Bot/Utilities.h"
#include "World/WorldSnapshot.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"
#include <iostream>
#include <vector>


/**
 * \brief A Bot which is able to decide whether there are team member fields next to its fields.
 */
class MyBot : public PlayerBot
{
public:
    // Overwrite this method as it gets called by the world on each turn
    void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        // Loop trough every Field using a FieldListIterator which automatically loops trough all existing fields of this team
        for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
             Iterator != Snapshot.GetFields().End();
             Iterator.Next())
        {
            // Get the CurrentField where the iterator is at
            Field* CurrentField = Iterator.Get();

            // You can access information about all fields next to the CurrentField by asking the WorldSnapshot
            if (Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP))
                // If the field above this field is owned by this team split downwards
                //                       The direction  , Cell count on this field     * 50%
                CurrentField->SplitCells(DIRECTION::DOWN, CurrentField->GetCellCount() * 0.5);
            else
                // If the field above this field is empty or owned by an enemy split upwards
                CurrentField->SplitCells(DIRECTION::UP, CurrentField->GetCellCount() * 0.5);

            // Split rightwards anyway
            CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount() * 0.5);

            // NOTE: You cannot split more cells than you own
            // (The move will be skipped and nothing will be split)
            // Also if you split more than 100 cells from two or more different fields onto
            // one fields they will be kept at 100. But this can be important for an attack
            // as another field can be owned by splitting i.e. 200 cells from three directions
            // while the other one only owns 50 cells and gets 100 new cells from one direction.
            
            // To see what else you can access have a look at the Field.h and the WorldSnapshot.h files
        }
    }
};

/**
 * \brief A bot which splits by looking at adjacent fields and checks for its own team fields.
 */
class MaxBot : public PlayerBot
{
public:
    void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
             Iterator != Snapshot.GetFields().End();
             Iterator.Next())
        {
            Field* CurrentField = Iterator.Get();

            if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::LEFT))
                CurrentField->SplitCells(DIRECTION::LEFT, CurrentField->GetCellCount()*0.5);
            else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP))
                CurrentField->SplitCells(DIRECTION::UP, CurrentField->GetCellCount()*0.5);
            else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::RIGHT))
                CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount()*0.5);
            else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::DOWN))
                CurrentField->SplitCells(DIRECTION::DOWN, CurrentField->GetCellCount()*0.5);

            if (Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::LEFT)  &&
                Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP)    &&
                Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::RIGHT) &&
                Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::DOWN))
            {
                CurrentField->SplitCells(DIRECTION::UP, RoundUp(CurrentField->GetCellCount(), 0.1));
                CurrentField->SplitCells(DIRECTION::LEFT, RoundUp(CurrentField->GetCellCount(), 0.1));
                CurrentField->SplitCells(DIRECTION::DOWN, RoundUp(CurrentField->GetCellCount(), 0.1));
                CurrentField->SplitCells(DIRECTION::RIGHT, RoundUp(CurrentField->GetCellCount(), 0.1));
            }
        }
    }
};

/**
 * \brief Another Bot just for demonstration purposes.
 */
class AnotherPlayerBot : public PlayerBot
{
public:
    // Simply overwrite the MakeTurn function to define the bots behaviour
    void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
             Iterator != Snapshot.GetFields().End();
             Iterator.Next())
        {
            Field* CurrentField = Iterator.Get();
            CurrentField->SplitCells(DIRECTION::UP, CurrentField->GetCellCount() * 0.1);
            CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount() * 0.1);
            CurrentField->SplitCells(DIRECTION::LEFT, CurrentField->GetCellCount() * 0.1);
            CurrentField->SplitCells(DIRECTION::DOWN, CurrentField->GetCellCount() * 0.1);
        }
    }
};

/**
 * \brief Bot
 */
class MinBot : public PlayerBot
{
public:
   void MakeTurn(const WorldSnapshot& Snapshot) override
    {
    //std::cout << "\n\nTurn " << Snapshot.GetTurn() << "\n";
        unsigned int Sum = 0;
        for (unsigned int i = Snapshot.GetTurn(); i < 25 && i > 0; i--)
        {
            Sum += i * 4;
        }
        unsigned int Count = 0;
        /*
        FieldList MyFields = Snapshot.GetFields();
        for (unsigned int count = 0; count < MyFields.GetSize(); count++)
        {
            Field* CurrentField;
            try {
            CurrentField = MyFields[count];
            } catch (std::exception &e) {
               std::cout << "ERROR: " << e.what() << "\n";
            }
            */
        for (FieldListIterator Iterator = Snapshot.GetFields().Begin();
             Iterator != Snapshot.GetFields().End();
             Iterator.Next())
        {
            Field* CurrentField = Iterator.Get();
            unsigned short Currentcellcount = CurrentField->GetCellCount();
            if (Snapshot.GetTurn() == 0)
            {
                CurrentField->SplitCellsAllDirections(21);
            } 
            else if (Count == 0)
            {
                if (Currentcellcount > 34)
                    CurrentField->SplitCellsAllDirections((Currentcellcount - 31) * 0.25);
            }
            else if (Snapshot.GetTurn() < 50)
            {                
                if (Count % 2)
                {
                    if (Count == (Sum - (2 * Snapshot.GetTurn()) + 1) && Currentcellcount > 11)
                    {
                        CurrentField->SplitCells(DIRECTION::RIGHT, 11);
                        CurrentField->SplitCells(DIRECTION::DOWN, Currentcellcount - 12);
                    }
                    else if (Count == (Sum - (4 * Snapshot.GetTurn()) + 1) && Currentcellcount > 11)
                    {
                        CurrentField->SplitCells(DIRECTION::UP, 11);
                        CurrentField->SplitCells(DIRECTION::RIGHT, Currentcellcount - 12);
                    }
                    else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP))
                    {
                        CurrentField->SplitCells(DIRECTION::UP, Currentcellcount * 0.5);
                        CurrentField->SplitCells(DIRECTION::RIGHT, (Currentcellcount - 1) * 0.5);                        
                    }
                    else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::DOWN))
                    {
                        CurrentField->SplitCells(DIRECTION::RIGHT, Currentcellcount * 0.5);
                        CurrentField->SplitCells(DIRECTION::DOWN, (Currentcellcount - 1) * 0.5);                        
                    }
                    else
                    {
                        CurrentField->SplitCells(DIRECTION::RIGHT, Currentcellcount - (Currentcellcount * 0.75));
                        CurrentField->SplitCells(DIRECTION::UP, Currentcellcount * 0.25);
                        CurrentField->SplitCells(DIRECTION::DOWN, Currentcellcount * 0.25);
                    }
                }
                else
                {
                    if (Count == Sum && Currentcellcount > 11)
                    {
                        CurrentField->SplitCells(DIRECTION::DOWN, 11);
                        CurrentField->SplitCells(DIRECTION::LEFT, Currentcellcount - 12);
                    }
                    else if (Count == (Sum - (2 * Snapshot.GetTurn())) && Currentcellcount > 11)
                    {
                        CurrentField->SplitCells(DIRECTION::LEFT, 11);
                        CurrentField->SplitCells(DIRECTION::UP, Currentcellcount - 12);
                    }
                    else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP))
                    {
                        CurrentField->SplitCells(DIRECTION::LEFT, Currentcellcount * 0.5);
                        CurrentField->SplitCells(DIRECTION::UP, (Currentcellcount - 1) * 0.5);                        
                    }
                    else if (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::DOWN))
                    {
                        CurrentField->SplitCells(DIRECTION::DOWN, Currentcellcount * 0.5);
                        CurrentField->SplitCells(DIRECTION::LEFT,(Currentcellcount - 1) * 0.5);                        
                    }
                    else
                    {
                        CurrentField->SplitCells(DIRECTION::LEFT, Currentcellcount - (Currentcellcount * 0.75));
                        CurrentField->SplitCells(DIRECTION::UP, Currentcellcount * 0.25);
                        CurrentField->SplitCells(DIRECTION::DOWN, Currentcellcount * 0.25);
                    }
                }      
            }      
            else if (Snapshot.GetTurn() > 135)
            {
                CurrentField->SplitCells(DIRECTION::RIGHT, CurrentField->GetCellCount() * 0.9);
            } 
            else
            {
                CurrentField->SplitCellsAllDirections(Currentcellcount * 0.15);
            }
            
            //std::cout << "\n" << Count << ": " << Currentcellcount << " - sum - " << Sum << "\n"; 
            Count++;
        }
                /*if((!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::UP)
                && !Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::LEFT)
                && !Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::RIGHT)) ||
                   (!Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::DOWN)
                && !Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::LEFT)
                && !Snapshot.GetAdjacentFieldOf(CurrentField, DIRECTION::RIGHT)))
                    Cornerpieces.push_back(CurrentField);
                */ 
    }
};
