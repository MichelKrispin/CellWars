#include "SFMLWindow.h"
#include <SFML/Graphics.hpp>
#include "World/Field.h"
#include "World/FieldList.h"
#include "World/FieldListIterator.h"
#include "World/ConfigurationLoader.h"
#include <iostream>
#include <sstream>

#define BUTTON_SIZE 50

SFMLWindow::SFMLWindow(const ConfigurationLoader* const Configuration)
    : Window(Configuration),
      _Window(nullptr),
      _FontExists(true),
      _Buttons{
         {{_Configuration->GetWindowSize() - BUTTON_SIZE*6,
           _Configuration->GetWindowSize()+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Red},

         {{_Configuration->GetWindowSize() - BUTTON_SIZE*4,
           _Configuration->GetWindowSize()+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Green},

         {{_Configuration->GetWindowSize() - BUTTON_SIZE*2,
           _Configuration->GetWindowSize()+20},
         BUTTON_SIZE,
         &_ButtonRectangle,
         sf::Color::Blue}
         }
{
    if (!_Font.loadFromFile(_Configuration->GetFontPath()))
    {
        std::cout << "ERROR :: LOADING FONT :: WINDOW :: at "  << _Configuration->GetFontPath() << "\n";
        _FontExists = false;
    }

    if (_FontExists)
    {
        _Text = new sf::Text;
        _Text->setFont(_Font);
        _Text->setCharacterSize(_Configuration->GetWindowSize()/10);
        _Text->setFillColor(sf::Color::White);
        _Text->setPosition(10, static_cast<float>(_Configuration->GetWindowSize()-10)); // 10px padding on left side
    }
    
    _ButtonRectangle = new sf::RectangleShape;
}

SFMLWindow::~SFMLWindow()
{
    delete _Window;
    delete _Text;
}

WindowEvent SFMLWindow::Display(const FieldList *Fields, const unsigned char &NumberOfTeams, const unsigned int &TurnNumber)
{
    if (_Window == nullptr)
        _Window = new sf::RenderWindow(
                sf::VideoMode(_Configuration->GetWindowSize(),
                              _Configuration->GetWindowSize() + _Configuration->GetWindowSize()/10), // Add a fifth to the height
                "Cell Wars");

    // First check whether the window is dead
    sf::Event event{};
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
                if (_Buttons[0].IsInside(LocalMousePosition))
                    return WindowEvent::Pause;
                if (_Buttons[1].IsInside(LocalMousePosition))
                    return WindowEvent::Play;
                if (_Buttons[2].IsInside(LocalMousePosition))
                    return WindowEvent::StepForward;

            }
        }
    }

    // Set the turn count as the text for the _Text
    if (_FontExists)
    {
        std::stringstream TextConversion;
        TextConversion << TurnNumber;
        _Text->setString(TextConversion.str());
    }

    // Create one rectangle and draw it multiple times
    sf::RectangleShape Rectangle;
    // Minus two for the outline
    Rectangle.setSize(sf::Vector2f(_Configuration->GetWindowSize() / _Configuration->GetGridSize() - 2.0f,
                                        _Configuration->GetWindowSize() / _Configuration->GetGridSize() - 2.0f));
    Rectangle.setOutlineColor(sf::Color::Black);
    Rectangle.setOutlineThickness(1.0f);

    // Reset the window
    _Window->clear(_Configuration->GetBackgroundColor());

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
                    // Casting from double to unsigned char as color channel only goes to 255 -> unsigned 8 bit integer value
                    Rectangle.setFillColor(sf::Color(
                        0, 0, static_cast<unsigned char>(Current->GetCellCount() * 255.0 / _Configuration->GetMaxCountPerField())));
                    break;
                case TEAM::RED:
                    Rectangle.setFillColor(sf::Color(
                        static_cast<unsigned char>(Current->GetCellCount() * 255.0 / _Configuration->GetMaxCountPerField()), 0, 0));
                    break;
                case TEAM::GREEN:
                    Rectangle.setFillColor(sf::Color(
                        0, static_cast<unsigned char>(Current->GetCellCount() * 255.0 / _Configuration->GetMaxCountPerField()), 0));
                    break;
                case TEAM::YELLOW:
                    Rectangle.setFillColor(sf::Color(
                        static_cast<unsigned char>(Current->GetCellCount() * 255.0 / _Configuration->GetMaxCountPerField()),
                        static_cast<unsigned char>(Current->GetCellCount() * 255.0 / _Configuration->GetMaxCountPerField()), 0));
                    break;
            }
            // Where it should be rendered
            Vector Position = Current->GetPosition();
            Rectangle.setPosition(Position.X, Position.Y);
            // Draw this rectangle
            _Window->draw(Rectangle);
        }
    }

    // Draw the text if the font was loaded
    if (_FontExists)
        _Window->draw(*_Text);

    // Draw the buttons
    for (auto &Button : _Buttons)
    {
        // For the hover color
        sf::Vector2i LocalMousePosition = sf::Mouse::getPosition(*_Window);
        Button.SetHover(Button.IsInside(LocalMousePosition));
        Button.Draw(_Window);
    }
    
    // Display everything drawn
    _Window->display();

    return WindowEvent::Nothing; // Everything is alright
}

void SFMLWindow::SetWinner(TEAM Team)
{
    // Initialize everything needed for the displaying
    // and then display it once
    sf::RectangleShape Rectangle;
    // Minus two for the outline
    Rectangle.setSize(sf::Vector2f(_Configuration->GetWindowSize() * 0.5f,
                                   _Configuration->GetWindowSize() * 0.5f));
    Rectangle.setOutlineColor(sf::Color::Black);
    Rectangle.setOutlineThickness(1.0f);
    Rectangle.setPosition(_Configuration->GetWindowSize() * 0.25f,
                          _Configuration->GetWindowSize() * 0.25f);

    std::string WinnerText;
    // Set the color of the rectangle to be that of the winner team
    // And also set the correct winner text
    switch (Team)
    {
        case TEAM::BLUE:
            Rectangle.setFillColor(sf::Color(0, 0, 255));
            WinnerText += "Blue";
            break;
        case TEAM::RED:
            Rectangle.setFillColor(sf::Color(255, 0, 0));
            WinnerText += "Red";
            break;
        case TEAM::GREEN:
            Rectangle.setFillColor(sf::Color(0, 255, 0));
            WinnerText += "Green";
            break;
        case TEAM::YELLOW:
            Rectangle.setFillColor(sf::Color(255, 255, 0));
            WinnerText += "Yellow";
            break;
    }
    WinnerText += " wins!";

    if (_FontExists)
    {
        _Text->setString(WinnerText);
        _Text->setPosition(_Configuration->GetWindowSize() * 0.28f,
                           _Configuration->GetWindowSize() * 0.45f);
    }
    
    // Reset the window
    _Window->clear(_Configuration->GetBackgroundColor());
    _Window->draw(Rectangle);
    if (_FontExists)
        _Window->draw(*_Text);
    _Window->display();


    // Loop as long as someone kills the window
    for (;;)
    {
        // First check if someone actually kills the window
        sf::Event event{};
        while (_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _Window->close();
                return;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                _Window->close();
                return;
            }
        }
    }
}
