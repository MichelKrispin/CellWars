#pragma once
#include "Window.h"
#include "World/WorldSnapshot.h"
#include <SFML/Graphics/Font.hpp>
#include "Renderer/WindowEvent.h"
#include "World/Vector.h"
#include "Button.h"

namespace sf {
    class RenderWindow; class Font; class Text; class RectangleShape;
}
class Configuration;

/**
 * \brief Window class to render out everything.
 *
 * Needs a FieldList pointer to all fields to render out every field
 * as there are positions saved.
 */
class SFMLWindow : public Window
{
public:
    /**
     * \brief Initializes the window with default values.
     * Height and width will be WINDOW_SIZE (800 by default).
     * Can be changed in the config.txt
     */
    SFMLWindow();
    ~SFMLWindow() override;

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
    WindowEvent Display(const FieldList *Fields, const unsigned char &NumberOfTeams, const unsigned int &TurnNumber) override;

    /**
     * \brief Sets a winner which ends the game.
     *
     * The winning team can also be a casted 0, 1, 2, 3.
     * 
     * \param Team The winning team.
     */
    void SetWinner(TEAM Team) override;

private:
    sf::RenderWindow* _Window;                        //< Pointer to the SFML Window drawing the stuff.
    sf::Font _Font;                                   //< The font used for the text.
    bool _FontExists;                                  //< Indicates whether the font exists.
    sf::Text* _Text;                                  //< Pointer to the text drawn.
    sf::RectangleShape* _ButtonRectangle;             //< Pointer a button rectangle drawn on the bottom.
    Button _Buttons[3];                               //< The buttons.

};
