#include "Button.h"
#include <SFML/Graphics/RectangleShape.hpp>

Button::Button(const Vector &Position,
               const unsigned int &ButtonSize,
               sf::RectangleShape* Rectangle,
               const sf::Color &BackgroundColor,
               const sf::Color &HoverColor)
    : _Position(Position),
      _ButtonSize(ButtonSize),
      _Rectangle(Rectangle),
      _BackgroundColor(BackgroundColor),
      _HoverColor(HoverColor),
      _HoverState(false)
{
}

Button::~Button() = default;

bool Button::IsInside(const Vector &Position) {
    return (Position.X > _Position.X &&
            Position.X < _Position.X + _ButtonSize &&
            Position.Y > _Position.Y &&
            Position.Y < _Position.Y + _ButtonSize);
}

void Button::SetHover(bool State) {
    _HoverState = State;
}

void Button::Draw() {
    _Rectangle->setFillColor(_BackgroundColor); // Set color of rectangle
    if (_HoverState)
        _Rectangle->setOutlineColor(_HoverColor);
    //return _Rectangle;
}
