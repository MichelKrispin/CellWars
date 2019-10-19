#ifndef _WINDOW_H
#define _WINDOW_H

#include "WindowEvent.h"
#include "Bot/Team.h"

class Configuration;
class FieldList;

class Window {
public:
    /**
     * \brief Initialize the window with a global configuration.
     *
     * This function doesn't need to be overridden.
     */
    Window();
    virtual ~Window();

    /**
     * \brief Display the window.
     *
     * The default function to call after all calculations are made.
     * This function should implement a window drawing function.
     * This windows should draw for the NumberOfTeams all elements in the
     * FieldList. The TurnNumber is given to make it possible to show it somehow.
     *
     * It should also handle all input events and return a WindowEvent accordingly.
     *
     * \param Fields A list for all fields which should be drawn
     * \param NumberOfTeams The number of teams playing.
     * \param TurnNumber The count of this round.
     *
     * \return Returns a window event according to any interactivity happened while displaying.
     */
    virtual WindowEvent Display(const FieldList* Fields, const unsigned char &NumberOfTeams, const unsigned int &TurnNumber) = 0;

    /**
     * \brief Sets a winner to end the game.
     *
     * This function should display the winner in a winner/end game screen.
     * After this method terminates the World will end the game.
     * The winning team can also be a cast to team 0, 1, 2, 3.
     *
     * \param Team The winning team.
     */
     virtual void SetWinner(TEAM Team) = 0;
};

#endif //_WINDOW_H
