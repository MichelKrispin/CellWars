#include "Bot/PlayerBot.h"
#include "Bot/EnemyBot.h"
#include "Bot/Utilities.h"
#include "World/WorldSnapshot.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"


/**
 * \brief A Bot which is able to decide whether there are team member fields next to its fields.
 */
class MyBot : public PlayerBot
{
    // Overwrite this method as it gets called by the world on each turn
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        // Loop trough every Field using a FieldListIterator which automatically loops trough all existing fields of this team
        for (FieldListIterator Iterator = Snapshot.GetFields(GetTeam()).Begin();
             Iterator != Snapshot.GetFields(GetTeam()).End();
             Iterator.Next())
        {
            // Get the CurrentField where the iterator is at
            Field* CurrentField = Iterator.Get();

            // You can access information about all fields next to the CurrentField by asking the WorldSnapshot
            if (Snapshot.GetAdjacentFieldOf(GetTeam(), CurrentField, DIRECTION::UP))
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
        }
    }
};


class AnotherEnemyBot : public EnemyBot
{
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        for (FieldListIterator Iterator = Snapshot.GetFields(GetTeam()).Begin();
             Iterator != Snapshot.GetFields(GetTeam()).End();
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
