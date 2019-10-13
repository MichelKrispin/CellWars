#ifndef CELLWARS_BUTTON_H
#define CELLWARS_BUTTON_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include "World/Vector.h"

namespace sf { class RectangleShape; class RenderWindow; }

/**
 * \brief A button which can be rendered on screen
 *
 * This button takes an already existing RectangleShape which will be changed within this button.
 * It is thought to be used with multiple buttons sharing the same RectangleShape.
 * These buttons are having all the same size.
 */
class Button {
public:
    /**
     * \brief The constructor for the button.
     *
     * The position and button will be just kept as a reference for manipulating the Rectangle later on.
     *
     * \param Position The position of this button.
     * \param ButtonSize Rectangular size
     * \param Rectangle The RectangleShape which will be manipulated within this button.
     * \param BackgroundColor The background color of this button.
     * \param HoverColor The hover color of this button. It defaults to white.
     */
    Button(const Vector &Position,
           const unsigned int &ButtonSize,
           sf::RectangleShape** Rectangle,
           const sf::Color &BackgroundColor,
           const sf::Color &HoverColor = sf::Color::White);

    /**
     * \brief The copy operator for the button.
     *
     * This constructor is used to assign a button inside of an array to a new button.
     *
     * \param Other The other button.
     */
    Button(const Button &Other);
    
    ~Button();

    /**
     * \brief Method to check whether a position is inside of this button.
     *
     * \param Position The position which will be checked for.
     * \return Returns true if the position is inside of this button.
     */
    bool IsInside(const sf::Vector2i &Position);

    /**
     * \brief Sets the hover for this button.
     *
     * This hover will set the internal state of the hover.
     * It will be used on the drawing method where it will change the Rectangle.
     *
     * \param State true if the hover should be activated, false otherwise.
     */
    void SetHover(bool State);

    /**
     * \brief Drawing this button at its position with maybe its hover activated.
     *
     * This method will change the Rectangle to which this button points to.
     */
    void Draw(sf::RenderWindow* Window);

private:
    const Vector _Position;         //< The position of this button which will be used for checking whether a position is inside.
    sf::RectangleShape** _Rectangle; //< A pointer to the pointer to the RectangleShape which will be used to draw this button.
    const unsigned int _ButtonSize;       //< The size of this button (Width and height)
    const sf::Color _BackgroundColor;     //< The background color of this button.
    const sf::Color _HoverColor;          //< The hover color of this button.
    bool _HoverState;           //< The state of the hover.
};


#endif //CELLWARS_BUTTON_H
