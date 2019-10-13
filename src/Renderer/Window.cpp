#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "World/Field.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"
#include <iostream>
#include <sstream>

#define BUTTON_SIZE 50

Window::Window()
    : _Buttons{
         {{WINDOW_SIZE - BUTTON_SIZE*6, WINDOW_SIZE+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Red},

         {{WINDOW_SIZE - BUTTON_SIZE*4, WINDOW_SIZE+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Green},

         {{WINDOW_SIZE - BUTTON_SIZE*2, WINDOW_SIZE+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Blue}
         },
    _isDead(false)
{
    _Window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + WINDOW_SIZE/10), // Add a fifth to the height
            "Cell Wars");

    if (!_Font.loadFromFile(FONT_PATH))
        std::cout << "ERROR :: LOADING FONT :: WINDOW :: at "  << FONT_PATH << "\n";

    _Text = new sf::Text;
    _Text->setFont(_Font);
    _Text->setCharacterSize(WINDOW_SIZE/10);
    _Text->setFillColor(sf::Color::White);
    _Text->setPosition(10, WINDOW_SIZE-10); // 10px padding on left side
    
    _ButtonRectangle = new sf::RectangleShape;
}

Window::~Window()
{
    delete _Window;
    delete _Text;
}

WindowEvent Window::Display(const FieldList *Fields, const unsigned char &NumberOfTeams, const unsigned int &TurnNumber)
{
    // First check whether the window is dead
    sf::Event event;
    while (_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _Window->close();
            return WindowEvent::Kill;
        }
        // Check for keyboard presses
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _Window->close();
                return WindowEvent::Kill;
            }
            else if (event.key.code == sf::Keyboard::Space)
                return WindowEvent::Pause; // TODO: Maybe change this Event to unpause toggle or similar
            else if (event.key.code == sf::Keyboard::Right)
                return WindowEvent::StepForward;
            else if (event.key.code == sf::Keyboard::Up)
                return WindowEvent::Play;
        }
        // Check for mouse clicks at correct positions
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i LocalMousePosition = sf::Mouse::getPosition(*_Window);
                // If inside of play button return play
                if (LocalMousePosition.x > WINDOW_SIZE - BUTTON_SIZE*6 && LocalMousePosition.y > WINDOW_SIZE + 20 &&
                    LocalMousePosition.x < WINDOW_SIZE - BUTTON_SIZE*5 &&
                    LocalMousePosition.y < WINDOW_SIZE + 20 + BUTTON_SIZE)
                    return WindowEvent::Pause; // TODO: Maybe change this Event to unpause toggle or similar

                if (LocalMousePosition.x > WINDOW_SIZE - BUTTON_SIZE*4 && LocalMousePosition.y > WINDOW_SIZE + 20 &&
                    LocalMousePosition.x < WINDOW_SIZE - BUTTON_SIZE*3 &&
                    LocalMousePosition.y < WINDOW_SIZE + 20 + BUTTON_SIZE)
                    return WindowEvent::Play;

                if (LocalMousePosition.x > WINDOW_SIZE - BUTTON_SIZE*2  && LocalMousePosition.y > WINDOW_SIZE + 20 &&
                    LocalMousePosition.x < WINDOW_SIZE - BUTTON_SIZE &&
                    LocalMousePosition.y < WINDOW_SIZE + 20 + BUTTON_SIZE)
                    return WindowEvent::StepForward;
            }
        }
    }

    // Set the turn count as the text for the _Text
    std::stringstream TextConversion;
    TextConversion << TurnNumber;
    _Text->setString(TextConversion.str());

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

    // Draw the text
    _Window->draw(*_Text);

    // Draw the buttons
    for (short i = 0; i < 3; ++i)
    {
        // For the hover color
        sf::Vector2i LocalMousePosition = sf::Mouse::getPosition(*_Window);
        if (_Buttons[i].IsInside(LocalMousePosition))
            _Buttons[i].SetHover(true);
        else
            _Buttons[i].SetHover(false);
        _Buttons[i].Draw(_Window);
    }
    
    // Display everything drawn
    _Window->display();

    return WindowEvent::Nothing; // Everything is alright
}

bool Window::isDead() const
{
    return _isDead;
}
