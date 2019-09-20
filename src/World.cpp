#include "World.h"
// TODO: Do this on another thread
#include "Window.h"
#include "FieldList.h"
#include "Configuration.h"

World& World::getWorld()
{
    static World instance;
    return instance;
}

World::World()
    : _Window()
{
    _WorldSnapshot = new WorldSnapshot;
    // TODO: Make this adjustable for multiple teams
    _Fields = new FieldList[2];
}

World::~World()
{
}

void World::Play(Bot* Blue, Bot* Red)
{
    for (unsigned int i = 0; i < MAX_TURN_COUNT; ++i)
    {
        // First make the turns for the bots
        Blue->MakeTurn(*_WorldSnapshot);
        Red->MakeTurn(*_WorldSnapshot);

        // Then calculate/execute their actions and check whether they are alright
        UpdateWorld();
    }

}

void World::UpdateWorld()
{
    // Looping trough all fields and applying the actions
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = _Fields[i].Begin();
             iterator != _Fields[i].End();
             iterator.Next())
        {

        }
    }
    // TODO: Make this more efficient. Maybe by saving the vectors and checking while looping once
    // After applying everything loop again and check whether some fields were killed
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = _Fields[i].Begin();
             iterator != _Fields[i].End();
             iterator.Next())
        {

        }
    }

    // TODO: Do this on another thread
    // After calculating everything draw everything
    _Window.Display(_Fields);
}

