#include "World.h"
#include "FieldList.h"
#include "WorldSnapshot.h"
#include <SFML/System/Clock.hpp>
#include <iostream>

World::World()
    : _Configuration(),
      _Window(&_Configuration),
      _Grid(&_Configuration),
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

    WindowEvent Event = WindowEvent::Nothing; // Used to get feedback of the window for interactivity
    bool Kill = false;                        // To indicate whether window should be killed afterwards
    bool isPaused = _Configuration.GetPauseOnStartup();         // Default value if starting with paused
    bool TimePaused = false;                  // To pause the turns for the turn time
    bool OneStepForward = false;              // To check whether to go only one step forward
    while (_WorldSnapshot->_TurnNumber < _Configuration.GetMaxTurnCount())
    {
        // If paused don't do anything
        if (!isPaused && !TimePaused)
        {
            _Clock->restart();

            // First make the turns for all bots
            for (unsigned char j = 0; j < _NumberOfBots; ++j)
            {
                // TODO: Check the duration time for the make turn function
                // and if one is above limit delete all of their actions (hehe)
                _Bots[j]->MakeTurn(_WorldSnapshot[_Bots[j]->GetTeamAsUnsignedInt()]);
            }

            _WorldSnapshot->_TurnNumber++;
            // After the turn update once
            _UpdateWorld();

            // Turn of the one step again so we really just took one step
            if (OneStepForward)
            {
                isPaused = true;
                OneStepForward = false;
            }

            // If one team has no fields anymore break
            for (unsigned char j = 0; j < _NumberOfBots; ++j)
            {
                if (!_WorldSnapshot[_Bots[j]->GetTeamAsUnsignedInt()].GetFields().GetSize())
                    return;
            }

        }

        // Pause as long as wer are below the turn duration
        TimePaused = _Clock->getElapsedTime().asMilliseconds() < _Configuration.GetTurnDurationInMs();

        Event = _RenderWorld(_WorldSnapshot->_TurnNumber);

        switch (Event)
        {
            case WindowEvent::Nothing:
                break;
            case WindowEvent::Kill:
                Kill = true;
                break;
            case WindowEvent::Pause:
                isPaused = true;
                break;
            case WindowEvent::Play:
                isPaused = false;
                break;
            case WindowEvent::StepForward:
                isPaused = false;
                OneStepForward = true;
                break;
        }
        if (Kill)
            break;

        // Reset the Event after using it once
        Event = WindowEvent::Nothing;
    }
}

bool World::_SetInputToLocalBots(Bot** Bots)
{
    // If the pointer itself is empty return false
    if (Bots == nullptr)
        return false;

    // Go trough all bots pointers and check how many exist
    unsigned char count = 0;
    for (unsigned char i = 0; i < 4; ++i)
    {
        // By this we know that at the next position there is an existing Bot
        if (dynamic_cast<Bot*>(Bots[i]) != nullptr && // Short-circuiting for testing if that pointer is null
            dynamic_cast<Bot*>(Bots[i])->GetTeamAsUnsignedInt() == -1) //TODO: This looks wrong
        {
            _Bots[count] = Bots[i];
            ++count;
        }
    }
    // If there is only one return false
    if (count <= 1)
        return false;
    
    _NumberOfBots = count;
    return true;
}

bool World::_Initialize()
{
    // Initialize as many fields and world snapshots as needed
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
        // from numbers on the grid to pixels
        Vector TranslatedStartingPosition = _Bots[i]->GetStartingPosition();
        TranslatedStartingPosition.X *= _Configuration.GetWindowSize() / _Configuration.GetGridSize();
        TranslatedStartingPosition.Y *= _Configuration.GetWindowSize() / _Configuration.GetGridSize();
        _Fields[_Bots[i]->GetTeamAsUnsignedInt()]._Add(
                Field(&_Configuration, _Bots[i]->GetTeam(), 100, TranslatedStartingPosition));
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
    // Looping trough all fields of all teams and applying the actions
    // (Settings the split values on the grid for each team)
    for (int i = 0; i < _NumberOfBots; ++i)
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

            // If sum exceeds cell count then skip this split
            if (SummedSplitValues > CurrentField->GetCellCount())
            {
                CurrentField->_ResetActions();
                continue;
            }

            if (CurrentActions.Up > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X, CurrentPosition.Y - _Configuration.GetWindowSize()/_Configuration.GetGridSize(),
                        static_cast<TEAM>(i), CurrentActions.Up);
            if (CurrentActions.Down > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X, CurrentPosition.Y + _Configuration.GetWindowSize()/_Configuration.GetGridSize(),
                        static_cast<TEAM>(i), CurrentActions.Down);
            if (CurrentActions.Left > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X - _Configuration.GetWindowSize()/_Configuration.GetGridSize(), CurrentPosition.Y,
                        static_cast<TEAM>(i), CurrentActions.Left);
            if (CurrentActions.Right > 0)
                _Grid.SetFieldValuesAt(
                        CurrentPosition.X + _Configuration.GetWindowSize()/_Configuration.GetGridSize(), CurrentPosition.Y,
                        static_cast<TEAM>(i), CurrentActions.Right);

            // After setting all those field values decrease the actual cell count of the current field
            CurrentField->_SetCellCount(CurrentField->GetCellCount()-SummedSplitValues);

            // Afterwards reset the actions
            CurrentField->_ResetActions();
            
            if (!_Configuration.GetIncreasingSplitValues())
                // And then increase all by 10%
                CurrentField->_IncreaseCellCount(0.1);
        }
    }
    // After applying everything calculate the grid
    _Grid.ComputeAllFields(_Fields, _NumberOfBots);

    if (_Configuration.GetIncreasingSplitValues())
    {
        for (int i = 0; i < _NumberOfBots; ++i)
        {
            for (FieldListIterator Iterator = _Fields[i].Begin();
                Iterator != _Fields[i].End();
                Iterator.Next())
            {
                // Increase all fields by 10%
                Iterator.Get()->_IncreaseCellCount(0.1);
            }
        }
    }
}

WindowEvent World::_RenderWorld(const unsigned int &TurnNumber)
{
    // TODO: Do this on another thread
    // After calculating everything draw everything
    return _Window.Display(_Fields, _NumberOfBots, TurnNumber);
}

