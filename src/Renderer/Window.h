#pragma once
#include "World/WorldSnapshot.h"

namespace sf { class RenderWindow; }

/**
 * \brief Window class to render out everything.
 *
 * Needs a FieldList pointer to all fields to render out every field
 * as there are positions saved.
 */
class Window
{
public:
    /**
     * \brief Initializes the window with default values.
     * Height and width will be WINDOW_SIZE (800 by default).
     * Can be changed in the Configuration.h
     */
    Window();
    ~Window();

    /**
     * \brief Display the window.
     * The default function to call after all calculations are made.
     * 
     * \param Fields A list for all fields which should be drawn
     * \param NumberOfTeams The number of teams playing.
     */
    void Display(const FieldList* Fields, unsigned char NumberOfTeams);

    /**
     * \brief Indicates whether the window was closed.
     *
     * \return Returns true when the window was closed.
     */
    bool isDead() const;

private:
    sf::RenderWindow* _Window; //< Pointer to the SFML Window drawing the stuff.
    bool _isDead;              //< Indicate whether the window was killed.

};
