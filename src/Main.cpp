#include "World/World.h"
#include "Bot/Examples.h"

int main()
{
    MyBot MyPlayer;
    PlayAgainstPlayerBot Player(DIRECTION::DOWN, TEAM::RED);
    AnotherEnemyBot Enemy;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&MyPlayer, &Player);
    return 0;
}
