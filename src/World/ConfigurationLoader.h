#ifndef _CONFIGURATIONLOADER_H
#define _CONFIGURATIONLOADER_H
#include <SFML/Graphics/Color.hpp>
#include <string>

/**
 * \brief Class to load the configuration dynamically.
 *
 * This class loads the configuration from the config.txt.
 * If it can't find the config.txt file then it uses default configurations.
 */
class ConfigurationLoader
{
public:
    ConfigurationLoader();
    virtual ~ConfigurationLoader();

    const unsigned int &GetMaxCountPerField() const;
    const unsigned int &GetWindowSize() const;
    const unsigned int &GetGridSize() const;
    const unsigned int &GetMaxTurnCount() const;
    const unsigned int &GetTurnDurationInMs() const;
    const sf::Color    &GetBackgroundColor() const;
    const std::string  &GetFontPath() const;
    const bool         &GetPauseOnStartup() const;
    const bool         &GetIncreasingSplitValues() const;

private:
    unsigned int _MaxCountPerField;
    unsigned int _WindowSize;
    unsigned int _GridSize;
    unsigned int _MaxTurnCount;
    unsigned int _TurnDurationInMs;
    sf::Color    _BackgroundColor;
    std::string  _FontPath;
    bool         _PauseOnStartup;
    bool         _IncreasingSplitValues;

};

#endif
