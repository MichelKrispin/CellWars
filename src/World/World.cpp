#include "World.h"
#include "FieldList.h"
#include "WorldSnapshot.h"
#include "Configuration.h"
#include <SFML/System/Clock.hpp>
#include <iostream>

World& World::GetWorld()
{
    static World instance;
    return instance;
}

World::World()
    : _Window(),
      _Grid(),
      _NumberOfBots(0)
{
    _Clock = new sf::Clock;
    // _WorldSnapshot and _Fields will be initialized in the right _Initialize() methods
    // as there might be more than 2 teams
    // Set all bots to be nullptr
    _Bots[0] = nullptr;
    _Bots[1] = nullptr;
    _Bots[2] = nullptr;
    _Bots[3] = nullptr;
}

World::~World()
{
    delete   _Clock;
    delete[] _WorldSnapshot;
    delete[] _Fields;
}

void World::Play(PlayerBot* Player1, PlayerBot* Player2)
{
    _Bots[0] = Player1;
    _Bots[1] = Player2;
    Play(_Bots);
}

void World::Play(Bot** Bots)
{
    // Save the input bots to the local _Bots array for as many bots as there might exist
    if (!_SetInputToLocalBots(Bots))
        return;

    // Initialize everything first and if there are errors quit
    if (!_Initialize())
        return;

    for (unsigned int i = 0; i < MAX_TURN_COUNT; ++i)
    {
        _Clock->restart();
        // TODO: Check the duration time for the make turn function
        // and if one is above limit delete all of their actions (hehe)
        
        // TODO: Change this to be more adjustable more multiple bots
        // First make the turns for all bots
        for (unsigned char i = 0; i < _NumberOfBots; ++i) 
        {
            _Bots[i]->MakeTurn(_WorldSnapshot[_Bots[i]->GetTeamAsUnsignedInt()]);
        }

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

bool World::_SetInputToLocalBots(Bot** Bots)
{
    // If the pointer itself is empty return false
    if (Bots == nullptr) // TODO: Same as Bots[0]?
        return false;

    // Go trough all bots pointers and check how many exist
    unsigned char count = 0;
    for (unsigned char i = 0; i < 4; ++i)
    {
        // By this we know that at the next position there is an existing Bot
        if (dynamic_cast<Bot*>(Bots[i])->GetTeamAsUnsignedInt() == -1)
        {
            _Bots[count] = Bots[i];
            ++count;
        }
    }
    // If there is only one return false
    if (count < 1)
        return false;
    
    _NumberOfBots = count;
    return true;
}

bool World::_Initialize()
{
    // Initalize as many fields and worldsnapshots as needed 
    _Fields = new FieldList[_NumberOfBots];
    _WorldSnapshot = new WorldSnapshot[_NumberOfBots];

    // Initialize the bots and fields for as many players as there are
    for (unsigned char i = 0; i < _NumberOfBots; ++i)
    {
        // Initialize the bots first
        _Bots[i]->_Initialize(
            static_cast<DIRECTION>(i), // Direction goes first LEFt, RIGHT, DOWN, UP
            static_cast<TEAM>(i));     // Team goes first BLUE, RED, GREEN, YELLOW

       
        // After initializing the players initialize the fields for two teams
        // Starting Positions have to be translated 
        // from pixels to numbers on the grid
        Vector TranslatedStartingPosition = _Bots[i]->GetStartingPosition();
        TranslatedStartingPosition.X *= WINDOW_SIZE / GRID_SIZE;
        TranslatedStartingPosition.Y *= WINDOW_SIZE / GRID_SIZE;
        _Fields[_Bots[i]->GetTeamAsUnsignedInt()]._Add(
                Field(_Bots[i]->GetTeam(), 100, TranslatedStartingPosition));
    }

    // Then the Grid can be initialized with the fields
    _Grid.Initialize(_Fields, _NumberOfBots); // Second argument is the number of teams

    // Then initialize the WorldSnapshot for all teams
    for (unsigned char i = 0; i < _NumberOfBots; ++i)
    {
        _WorldSnapshot[_Bots[i]->GetTeamAsUnsignedInt()]   // Initalize Snapshot at first position
            ._Initialize(_Bots[i]->GetTeam(), &_Fields[_Bots[i]->GetTeamAsUnsignedInt()], &_Grid);
    }
    return true;
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

