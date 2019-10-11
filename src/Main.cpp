#include "World/World.h"
#include "Bot/Examples.h"

// Keyboard shortcuts:
// Stop: Space
// Play: Arrow-Up
// Move one step forward (on pause): Arrow-right
int main()
{
    World& GameWorld = World::GetWorld();

    MyBot Player;
    MaxBot MyPlayer;
    AnotherPlayerBot Enemy;
    Bot* Bots[3]; // For a 2-4 player game
    Bots[0] = &Player;
    Bots[1] = &MyPlayer;
    Bots[2] = &Enemy;
    //GameWorld.Play(&Player, &MyPlayer); // For a two player game
    GameWorld.Play(Bots);
    return 0;
}
