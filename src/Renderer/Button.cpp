#include "Button.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Button::Button(const Vector &Position,
               const unsigned int &ButtonSize,
               sf::RectangleShape** Rectangle,
               const sf::Color &BackgroundColor,
               const sf::Color &HoverColor)
    : _Position(Position),
      _Rectangle(Rectangle),
      _ButtonSize(ButtonSize),
      _BackgroundColor(BackgroundColor),
      _HoverColor(HoverColor),
      _HoverState(false)
{
}


Button::Button(const Button &Other)
    : _Position(Other._Position),
      _Rectangle(Other._Rectangle),
      _ButtonSize(Other._ButtonSize),
      _BackgroundColor(Other._BackgroundColor),
      _HoverColor(Other._HoverColor),
      _HoverState(false)
{
}

Button::~Button() = default;

bool Button::IsInside(const sf::Vector2i &Position) {
    return (static_cast<unsigned int>(Position.x) > _Position.X &&
            static_cast<unsigned int>(Position.x) < _Position.X + _ButtonSize &&
            static_cast<unsigned int>(Position.y) > _Position.Y &&
            static_cast<unsigned int>(Position.y) < _Position.Y + _ButtonSize);
}

void Button::SetHover(bool State) {
    _HoverState = State;
}

void Button::Draw(sf::RenderWindow* Window) {
    _Rectangle[0]->setPosition(
            { static_cast<float>(_Position.X),
              static_cast<float>(_Position.Y) }); // Set color of rectangle
    _Rectangle[0]->setFillColor(_BackgroundColor); // Set color of rectangle
    _Rectangle[0]->setOutlineThickness(5.0f); // Set size of outline
    if (_HoverState) // Set hover color or black outline
        _Rectangle[0]->setOutlineColor(_HoverColor);
    else
        _Rectangle[0]->setOutlineColor(sf::Color::Black);
    // Set size
    _Rectangle[0]->setSize({ static_cast<float>(_ButtonSize),
                          static_cast<float>(_ButtonSize) });
    // Draw using the rectangle
    Window->draw(**_Rectangle);
}
