#include "World/World.h"
#include "Bot/PlayerBot.h"
#include "Bot/EnemyBot.h"
#include "Bot/Utilities.h"

class MyBot : public PlayerBot
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
        }
    }
};

class AnotherBot : public EnemyBot
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
        }
    }
};

int main()
{
    //PlayerBot Player;
    //EnemyBot  Enemy;
    MyBot Player;
    AnotherBot Player2;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&Player, &Player2);
    return 0;
}
