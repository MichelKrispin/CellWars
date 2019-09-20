#include "World.h"
#include "Window.h"
#include "FieldList.h"
#include "Configuration.h"

World& World::getWorld()
{
    static World instance;
    return instance;
}

World::World()
    : _Window(),
      _Clock()
{
    _WorldSnapshot = new WorldSnapshot;
    // TODO: Make this adjustable for multiple teams
    _Fields = new FieldList[2];
}

World::~World()
{
    delete _WorldSnapshot;
    delete[] _Fields;
}

void World::Play(Bot* Blue, Bot* Red)
{
    // Initialize both teams first fields
    // TODO: Raise an exception or similar if both starting positions are the same
    // Starting Positions will be numbers on the grid and are pixels now
    Vector BlueStartingPosition = Blue->getStartingPosition();
    BlueStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    BlueStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[0].Add(Field(100, BlueStartingPosition));
    Vector RedStartingPosition = Red->getStartingPosition();
    RedStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    RedStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[1].Add(Field(100, RedStartingPosition));

    for (unsigned int i = 0; i < MAX_TURN_COUNT; ++i)
    {
        _Clock.restart();
        // TODO: Check the duration time for the make turn function
        // First make the turns for the bots
        Blue->MakeTurn(*_WorldSnapshot);
        Red->MakeTurn(*_WorldSnapshot);

        // Only make a turn after the turn duration is exceeded
        bool Kill = false;
        while (_Clock.getElapsedTime().asMilliseconds() < TURN_DURATION_IN_MS)
        {
            // Then calculate/execute their actions and check whether they are alright
            Kill = UpdateWorld();
        }
        if (Kill)
            break;
    }

}

bool World::UpdateWorld()
{
    // Looping trough all fields and applying the actions
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = _Fields[i].Begin();
             iterator != _Fields[i].End();
             iterator.Next())
        {
            Field* Current = iterator.Get();
            // Split according to the actions without modifying them
            Current->_Actions;

            // Afterwards reset the actions
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
    
    // Return the death status of the window
    return _Window.isDead();
}

