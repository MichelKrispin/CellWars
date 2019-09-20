#include "World.h"
#include "Bot.h"

int main()
{
    Bot a;
    Bot b;
    World& GameWorld = World::getWorld();
    GameWorld.Play(&a, &b);
    return 0;
}
