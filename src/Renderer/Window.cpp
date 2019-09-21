#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"

Window::Window()
    : _isDead(false)
{
    _Window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Cell Wars");
}

Window::~Window()
{
    delete _Window;
}

void Window::Display(const FieldList* Fields)
{
    // First check whether the window is dead
    sf::Event event;
    while (_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _Window->close();
            _isDead = true;
        }
    }

    // Create one rectangle and draw it multiple times
    sf::RectangleShape Rectangle;
    // Minus two for the outline
    Rectangle.setSize(sf::Vector2f(WINDOW_SIZE / GRID_SIZE - 2.0f, WINDOW_SIZE / GRID_SIZE - 2.0f));
    Rectangle.setOutlineColor(sf::Color::Black);
    Rectangle.setOutlineThickness(1.0f);

    // Reset the window
    _Window->clear(sf::Color::BACKGROUND_COLOR);

    // Looping trough all of the Fields
    for (int i = 0; i < 2; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = Fields[i].Begin();
             iterator != Fields[i].End();
             iterator.Next())
        {
            Field* Current = iterator.Get();
            
            // How strong the field should be rendered
            // TODO: Make this adjustable for more Teams
            // If we are drawing for the first team take the last channel
            if (i) // Red team
                // TODO: Change the 2.55 as they are just working if MAX_COUNT = 100
                Rectangle.setFillColor(sf::Color(Current->GetCellCount() * 2.55, 0, 0));
            else   // Blue team
                Rectangle.setFillColor(sf::Color(0, 0, Current->GetCellCount() * 2.55));

            // Where it should be rendered
            Vector Position = Current->GetPosition();
            Rectangle.setPosition(Position.X, Position.Y);
            // Draw this rectangle
            _Window->draw(Rectangle);
        }
    }

    // Display everything drawn
    _Window->display();
}

bool Window::isDead() const
{
    return _isDead;
}
