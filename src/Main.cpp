#include "World.h"
#include "Bot.h"

#include <SFML/Graphics.hpp>
#include "Configuration.h"
int main()
{
    Bot a({5, 5}, TEAM::BLUE);
    Bot b({20, 20}, TEAM::RED);
    World& GameWorld = World::getWorld();
    GameWorld.Play(&a, &b);
    return 0;
}
