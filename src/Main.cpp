#include "World/World.h"
#include "Bot/Examples.h"

class MaxBot : public EnemyBot
{
public:
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override
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

int main()
{
    MyBot Player;
    MaxBot MyPlayer;
    //PlayAgainstPlayerBot Player(DIRECTION::RIGHT, TEAM::RED);
    AnotherEnemyBot Enemy;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&Player, &MyPlayer);
    return 0;
}
