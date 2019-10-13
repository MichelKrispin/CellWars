#pragma once
#include "World/WorldSnapshot.h"
#include <SFML/Graphics/Font.hpp>
#include "Renderer/WindowEvent.h"
#include "World/Vector.h"
#include "Button.h"

namespace sf {
    class RenderWindow; class Font; class Text; class RectangleShape;
}

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
     * \param TurnNumber The count of this round.
     *
     * \return Returns a window event according to any interactivity happened while displaying.
     */
    WindowEvent Display(const FieldList *Fields, const unsigned char &NumberOfTeams, const unsigned int &TurnNumber);

    /**
     * \brief Indicates whether the window was closed.
     *
     * \return Returns true when the window was closed.
     */
    bool isDead() const;

private:
    sf::RenderWindow* _Window;            //< Pointer to the SFML Window drawing the stuff.
    sf::Font _Font;                       //< The font used for the text.
    sf::Text* _Text;                      //< Pointer to the text drawn.
    sf::RectangleShape* _ButtonRectangle; //< Pointer a button rectangle drawn on the bottom.
    Button _Buttons[3];                   //< The buttons.
    bool _isDead;                         //< Indicate whether the window was killed.

};
