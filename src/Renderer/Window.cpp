#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "World/Field.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"

Window::Window()
    : _isDead(false)
{
    _Window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Cell Wars");
}

Window::~Window()
{
    delete _Window;
}

void Window::Display(const FieldList* Fields, unsigned char NumberOfTeams)
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
    for (int i = 0; i < NumberOfTeams; ++i) // 2 for team size
    {
        for (FieldListIterator iterator = Fields[i].Begin();
             iterator != Fields[i].End();
             iterator.Next())
        {
            Field* Current = iterator.Get();
            
            // How strong the field should be rendered
            // If we are drawing for the first team take the last channel
            switch (static_cast<TEAM>(i))
            {
                case TEAM::BLUE:
                    Rectangle.setFillColor(sf::Color(0, 0, Current->GetCellCount() * 255.0 / MAX_COUNT_PER_FIELD));
                    break;
                case TEAM::RED:
                    Rectangle.setFillColor(sf::Color(Current->GetCellCount() * 255.0 / MAX_COUNT_PER_FIELD, 0, 0));
                    break;
                case TEAM::GREEN:
                    Rectangle.setFillColor(sf::Color(0, Current->GetCellCount() * 255.0 / MAX_COUNT_PER_FIELD, 0));
                    break;
                case TEAM::YELLOW:
                    Rectangle.setFillColor(sf::Color(Current->GetCellCount() * 255.0 / MAX_COUNT_PER_FIELD, Current->GetCellCount() * 255.0 / MAX_COUNT_PER_FIELD, 0));
                    break;
            }
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
