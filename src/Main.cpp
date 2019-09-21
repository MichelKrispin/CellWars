#include "World.h"
#include "PlayerBot.h"
#include "EnemyBot.h"

int main()
{
    PlayerBot Player;
    EnemyBot  Enemy;
    World& GameWorld = World::getWorld();
    GameWorld.Play(&Player, &Enemy);
    return 0;
}
