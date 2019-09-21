#pragma once
#include "World/WorldSnapshot.h"

namespace sf {
    class RenderWindow;
}

class Window
{
public:
    /**
     * \brief Initializes the window with default values.
     * Height and width will be 800 by default.
     * Can be changed in the Configuration.h
     */
    Window();
    ~Window();

    /**
     * \brief Display the window.
     * The default function to call after all calculations are made.
     * 
     * \param Fields A list for all fields which should be drawn
     */
    void Display(const FieldList* Fields);

    /**
     * \brief Indicates whether the window was closed.
     *
     * \return Returns true when the window was closed.
     */
    bool isDead() const;

private:
    sf::RenderWindow* _Window; //< Pointer to the SFML Window drawing the stuff.
    bool _isDead; //< Indicate whether the window was killed.

};
