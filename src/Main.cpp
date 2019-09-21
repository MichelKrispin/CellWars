#include "World/World.h"
#include "Bot/PlayerBot.h"
#include "Bot/EnemyBot.h"

class MyBot : public PlayerBot
{
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override
    {
        for (FieldListIterator Iterator = Snapshot.GetFields(GetTeam()).Begin();
             Iterator != Snapshot.GetFields(GetTeam()).End();
             Iterator.Next())
        {
            Field* CurrentField = Iterator.Get();
            CurrentField->SplitCells(DIRECTION::UP, 30);
            CurrentField->SplitCells(DIRECTION::DOWN, 30);
            CurrentField->SplitCells(DIRECTION::RIGHT, 30);
            CurrentField->SplitCells(DIRECTION::LEFT, 30);
        }
    }
};

int main()
{
    PlayerBot Player;
    EnemyBot  Enemy;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&Player, &Enemy);
    return 0;
}
