#include "World.h"
#include "FieldList.h"
#include "Configuration.h"
#include <SFML/System/Clock.hpp>

World& World::GetWorld()
{
    static World instance;
    return instance;
}

World::World()
    : _Window(),
      _Grid()
{
    _Clock = new sf::Clock;
    _WorldSnapshot = new WorldSnapshot;
    // TODO: Make this adjustable for multiple teams
    _Fields = new FieldList[2];
}

World::~World()
{
    delete _Clock;
    delete _WorldSnapshot;
    delete[] _Fields;
}

void World::Play(PlayerBot* Player, EnemyBot* Enemy)
{
    Play(dynamic_cast<Bot*>(Player),
         dynamic_cast<Bot*>(Enemy));
}

void World::Play(Bot* Blue, Bot* Red)
{
    // Initialize everything first
    _Initialize(Blue, Red);

    for (unsigned int i = 0; i < MAX_TURN_COUNT; ++i)
    {
        _Clock->restart();
        // TODO: Check the duration time for the make turn function
        // First make the turns for the bots
        Blue->MakeTurn(*_WorldSnapshot);
        Red->MakeTurn(*_WorldSnapshot);
        _WorldSnapshot->_TurnNumber++;

        // Only make a turn after the turn duration is exceeded
        bool Kill = false;
        while (_Clock->getElapsedTime().asMilliseconds() < TURN_DURATION_IN_MS)
        {
            // Then calculate/execute their actions and check whether they are alright
            Kill = _UpdateWorld();
        }
        if (Kill)
            break;
    }

}

bool World::_UpdateWorld()
{
    // Looping trough all fields and applying the actions
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator Iterator = _Fields[i].Begin();
             Iterator != _Fields[i].End();
             Iterator.Next())
        {
            Field* CurrentField = Iterator.Get();
            
            // Split according to the actions without modifying them
            Actions &CurrentActions  = CurrentField->_Actions;

            // TODO: If sum of all action variables exceed the cells of the CurrentField
            // raise an exception
            const Vector &CurrentPosition = CurrentField->GetPosition();
            if (CurrentActions.Up > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X, CurrentPosition.Y - WINDOW_SIZE/GRID_SIZE,
                        static_cast<TEAM>(i), CurrentActions.Up);
            if (CurrentActions.Down > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X, CurrentPosition.Y + WINDOW_SIZE/GRID_SIZE,
                        static_cast<TEAM>(i), CurrentActions.Down);
            if (CurrentActions.Left > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X - WINDOW_SIZE/GRID_SIZE, CurrentPosition.Y,
                        static_cast<TEAM>(i), CurrentActions.Left);
            if (CurrentActions.Right > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X + WINDOW_SIZE/GRID_SIZE, CurrentPosition.Y,
                        static_cast<TEAM>(i), CurrentActions.Right);

            // Afterwards reset the actions
            CurrentField->_ResetActions();
        }
    }
    // After applying everything calculate the grid
    _Grid.ComputeAllFields(_Fields);
    

    // TODO: Do this on another thread
    // After calculating everything draw everything
    _Window.Display(_Fields);
    
    // Return the death status of the window
    return _Window.isDead();
}

void World::_Initialize(Bot* Blue, Bot* Red)
{
    // TODO: Raise an exception or similar if both starting positions are the same
    // Initialize both teams first fields
    /*
    if (Blue->GetStartingPosition())
    {

    }
    */
    
    // Starting Positions will be numbers on the grid and are pixels now
    Vector BlueStartingPosition = Blue->GetStartingPosition();
    BlueStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    BlueStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[static_cast<unsigned int>(TEAM::BLUE)]._Add(
            Field(TEAM::BLUE, 100, BlueStartingPosition));

    Vector RedStartingPosition = Red->GetStartingPosition();
    RedStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    RedStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[static_cast<unsigned int>(TEAM::RED)]._Add(
            Field(TEAM::RED, 100, RedStartingPosition));

    // Then initialize the grid to be a reference to the created fields
    _Grid.Initialize(_Fields, 2); // Second argument is the number of teams

    // Then initialize the WorldSnapshot
    // TODO: Make this snapshot prettier
    _WorldSnapshot->Fields = _Fields;


}

