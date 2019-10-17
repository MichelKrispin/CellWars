#include "ConfigurationLoader.h"
#include <fstream>
#include <iostream>

// Default values
ConfigurationLoader::ConfigurationLoader()
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

ConfigurationLoader::~ConfigurationLoader() = default;

const unsigned int& ConfigurationLoader::GetMaxCountPerField() const
{
    return _MaxCountPerField;
}

const unsigned int& ConfigurationLoader::GetWindowSize() const
{
    return _WindowSize;
}

const unsigned int& ConfigurationLoader::GetGridSize() const
{
    return _GridSize;
}

const unsigned int& ConfigurationLoader::GetMaxTurnCount() const
{
    return _MaxTurnCount;
}

const unsigned int& ConfigurationLoader::GetTurnDurationInMs() const
{
    return _TurnDurationInMs;
}

const sf::Color& ConfigurationLoader::GetBackgroundColor() const
{
    return _BackgroundColor;
}

const std::string& ConfigurationLoader::GetFontPath() const
{
    return _FontPath;
}

const bool& ConfigurationLoader::GetPauseOnStartup() const
{
    return _PauseOnStartup;
}

const bool& ConfigurationLoader::GetIncreasingSplitValues() const
{
    return _IncreasingSplitValues;
}
