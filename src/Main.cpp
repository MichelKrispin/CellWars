#include "World/World.h"
#include "Bot/Examples.h"

int main()
{
    //PlayerBot Player;
    //EnemyBot  Enemy;
    MyBot Player;
    AnotherEnemyBot Player2;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&Player, &Player2);
    return 0;
}
