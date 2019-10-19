#include "Configuration.h"
#include <fstream>
#include <iostream>

Configuration &Configuration::Get() {
    static Configuration Instance;
    return Instance;
}

// Default values
Configuration::Configuration()
    : _MaxCountPerField(100),
      _WindowSize(800),
      _GridSize(50),
      _MaxTurnCount(1000),
      _TurnDurationInMs(50),
      _BackgroundColor(sf::Color::Black),
      _FontPath("arial.ttf"),
      _PauseOnStartup(false),
      _IncreasingSplitValues(true)
{
    std::string Line; // Buffer for each line
    // Open up the file
    std::ifstream ConfigurationFile("..\\misc\\config.txt");
    if (!ConfigurationFile.is_open()) // If file is not open return
    {
        std::cout << "Could not find the config.txt - Initializing with default values\n";
        return;
    }

    // Read the input line by line
    while (std::getline(ConfigurationFile, Line))
    {
        // TODO: Add empty spaces to continue clause
        if (Line.rfind("//", 0) == 0)
            continue;
        if (Line.rfind("MAX_COUNT_PER_FIELD", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            // TODO: Check if there exists string to unsigned int function
            _MaxCountPerField = static_cast<unsigned int>(std::stoi(Line, nullptr, 0));
        }
        else if (Line.rfind("WINDOW_SIZE", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _WindowSize = static_cast<unsigned int>(std::stoi(Line, nullptr, 0));
        }
        else if (Line.rfind("GRID_SIZE", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _GridSize = static_cast<unsigned int>(std::stoi(Line, nullptr, 0));
        }
        else if (Line.rfind("TURN_DURATION_IN_MS", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _TurnDurationInMs = static_cast<unsigned int>(std::stoi(Line, nullptr, 0));
        }
        else if (Line.rfind("BACKGROUND_COLOR", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            if (Line == "White")
                _BackgroundColor = sf::Color::White;
            else
                _BackgroundColor = sf::Color::Black;
        }
        else if (Line.rfind("FONT_PATH", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _FontPath = Line;
        }
        else if (Line.rfind("PAUSE_ON_STARTUP", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _PauseOnStartup = Line == "true";
        }
        else if (Line.rfind("INCREASING_SPLIT_VALUES", 0) == 0)
        {
            std::getline(ConfigurationFile, Line);
            _IncreasingSplitValues = Line == "true";
        }
    }
}

Configuration::~Configuration() = default;

const unsigned int& Configuration::MaxCountPerField() const
{
    return _MaxCountPerField;
}

const unsigned int& Configuration::WindowSize() const
{
    return _WindowSize;
}

const unsigned int& Configuration::GridSize() const
{
    return _GridSize;
}

const unsigned int& Configuration::MaxTurnCount() const
{
    return _MaxTurnCount;
}

const unsigned int& Configuration::TurnDurationInMs() const
{
    return _TurnDurationInMs;
}

const sf::Color& Configuration::BackgroundColor() const
{
    return _BackgroundColor;
}

const std::string& Configuration::FontPath() const
{
    return _FontPath;
}

const bool& Configuration::PauseOnStartup() const
{
    return _PauseOnStartup;
}

const bool& Configuration::IncreasingSplitValues() const
{
    return _IncreasingSplitValues;
}
