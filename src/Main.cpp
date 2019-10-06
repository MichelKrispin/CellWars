#include "World/World.h"
#include "Bot/Examples.h"

int main()
{
    MyBot Player;
    MaxBot MyPlayer;
    Bot* Bots[2];
    Bots[0] = &Player;
    Bots[1] = &MyPlayer;
    World& GameWorld = World::GetWorld();
    GameWorld.Play(&Player, &MyPlayer);
    //GameWorld.Play(&Player, &MyPlayer);
    //GameWorld.Play(Bots);
    return 0;
}
