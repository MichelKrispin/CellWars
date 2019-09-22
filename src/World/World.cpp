#include "World.h"
#include "FieldList.h"
#include "WorldSnapshot.h"
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
    // TODO: Make this adjustable for multiple teams
    _WorldSnapshot = new WorldSnapshot[2]; 
    _Fields = new FieldList[2];
}

World::~World()
{
    delete   _Clock;
    delete[] _WorldSnapshot;
    delete[] _Fields;
}

void World::Play(PlayerBot* Player1, PlayerBot* Player2)
{
    Play(dynamic_cast<Bot*>(Player1),
         dynamic_cast<Bot*>(Player2));
}

void World::Play(PlayerBot* Player, EnemyBot* Enemy)
{
    Play(dynamic_cast<Bot*>(Player),
         dynamic_cast<Bot*>(Enemy));
}

bool World::_Initialize(Bot* Player, Bot* Enemy)
{
    // TODO: Output an error message or something
    // Quit if both teams are the same or if the starting positions are the same
    if (Player->GetStartingPosition() == Enemy->GetStartingPosition()
     || Player->GetTeam()             == Enemy->GetTeam())
        return false;
    
    // TODO: Fix teams to be that one of the bots
    // Initialize both teams first fields
    // Starting Positions will be numbers on the grid and are pixels now
    Vector BlueStartingPosition = Player->GetStartingPosition();
    BlueStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    BlueStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[static_cast<unsigned int>(TEAM::BLUE)]._Add(
            Field(TEAM::BLUE, 100, BlueStartingPosition));

    Vector RedStartingPosition = Enemy->GetStartingPosition();
    RedStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
    RedStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
    _Fields[static_cast<unsigned int>(TEAM::RED)]._Add(
            Field(TEAM::RED, 100, RedStartingPosition));

    // Then initialize the grid to be a reference to the created fields
    _Grid.Initialize(_Fields, 2); // Second argument is the number of teams

    // Then initialize the WorldSnapshot
    // TODO: Make this snapshot prettier
    _WorldSnapshot[static_cast<unsigned int>(TEAM::BLUE)]
        ._Initialize(TEAM::BLUE, &_Fields[static_cast<unsigned int>(TEAM::BLUE)], &_Grid);
    _WorldSnapshot[static_cast<unsigned int>(TEAM::RED)]
        ._Initialize(TEAM::BLUE, &_Fields[static_cast<unsigned int>(TEAM::RED)], &_Grid);
    return true;
}

void World::Play(Bot* Player, Bot* Enemy)
{
    // Initialize everything first and if there are errors quit
    if (!_Initialize(Player, Enemy))
        return;

    for (unsigned int i = 0; i < MAX_TURN_COUNT; ++i)
    {
        _Clock->restart();
        // TODO: Check the duration time for the make turn function
        // and if one is above limit delete all of their actions (hehe)
        
        // First make the turns for the bots
        Player->MakeTurn(_WorldSnapshot[static_cast<int>(TEAM::BLUE)]);
        Enemy->MakeTurn(_WorldSnapshot[static_cast<int>(TEAM::RED)]);
        _WorldSnapshot->_TurnNumber++;
        // After the turn update once
        _UpdateWorld();

        // Only make a turn after the turn duration is exceeded
        bool Kill = false;
        // Render as long as we are below the turn duration (mostly for responsiveness)
        while (_Clock->getElapsedTime().asMilliseconds() < TURN_DURATION_IN_MS)
            Kill = _RenderWorld();
        if (Kill)
            break;
    }
}

void World::_UpdateWorld()
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

            // raise an exception
            const Vector &CurrentPosition = CurrentField->GetPosition();
            const unsigned int SummedSplitValues = 
                CurrentActions.Up  + CurrentActions.Down +
                CurrentActions.Left + CurrentActions.Right;

            // TODO: If sum of all action variables exceed the cells of the CurrentField
            // If sum exceeds cell count then skip this split
            if (SummedSplitValues > CurrentField->GetCellCount())
                continue;

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

            // After setting all those field values decrease the actual cell count of the current field
            CurrentField->_SetCellCount(CurrentField->GetCellCount()-SummedSplitValues);

            // Afterwards reset the actions
            CurrentField->_ResetActions();
            
            // And then increase all by 10%
            CurrentField->_IncreaseCellCount(0.1);
        }
    }
    // After applying everything calculate the grid
    _Grid.ComputeAllFields(_Fields);
}

bool World::_RenderWorld()
{
    // TODO: Do this on another thread
    // After calculating everything draw everything
    _Window.Display(_Fields);
    
    // Return the death status of the window
    return _Window.isDead();
}

