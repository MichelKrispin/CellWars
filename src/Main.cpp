#include "World/World.h"
#include "Bot/PlayerBot.h"
#include "Bot/EnemyBot.h"

int main()
{
    PlayerBot Player;
    EnemyBot  Enemy;
    World& GameWorld = World::getWorld();
    GameWorld.Play(&Player, &Enemy);
    return 0;
}
