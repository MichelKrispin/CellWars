#ifndef _CONFIGURATIONLOADER_H
#define _CONFIGURATIONLOADER_H
#include <SFML/Graphics/Color.hpp>
#include <string>

/**
 * \brief Class to load the configuration dynamically.
 *
 * This class loads the configuration from the config.txt.
 * If it can't find the config.txt file then it uses default configurations.
 * The default values for each value can be found in the comments of the private variables.
 */
class ConfigurationLoader
{
public:
    /**
     * \brief Initialize the configuration.
     *
     * If the configuration file can't be found then the
     * default values will be used. A message will be printed
     * to console if this happens.
     */
    ConfigurationLoader();
    virtual ~ConfigurationLoader();

    /**
     * \brief Get the maximal cell count per field
     * \return The count as an unsigned int.
     */
    const unsigned int &GetMaxCountPerField() const;

    /**
     * \brief Get the window size in pixel.
     * \return The window size as an unsigned int.
     */
    const unsigned int &GetWindowSize() const;

    /**
     * \brief Get the grid size.
     * \return The grid size as an unsigned int.
     */
    const unsigned int &GetGridSize() const;

    /**
     * \brief Get the maximal number of rounds.
     * \return The maximal turn count as an unsigned int.
     */
    const unsigned int &GetMaxTurnCount() const;

    /**
     * \brief Get the turn duration in milliseconds.
     * \return The duration as an unsigned int.
     */
    const unsigned int &GetTurnDurationInMs() const;

    // TODO: Make this independent of SFML -> maybe return as a string
    /**
     * \brief Get the background color.
     * This can be white or black and is black by default.
     * Note that white can be helpful for a more distinct
     * look on which fields are possessed.
     *
     * \return The background color as an SFML color.
     */
    const sf::Color    &GetBackgroundColor() const;

    /**
     * \brief Get the font search path.
     * Path to the font relative from the working directory.
     *
     * \return The font search path as a string.
     */
    const std::string  &GetFontPath() const;

    /**
     * \brief Whether to pause on startup.
     * \return True if pausing on turn 0.
     */
    const bool         &GetPauseOnStartup() const;

    /**
     * \brief Whether the splitted values will be increased directly after splitting.
     * If false then the splitted values will not be increased right away. So only
     * the fields you already possess will be increased.
     *
     * \return True if the splitted values should be splitted.
     */
    const bool         &GetIncreasingSplitValues() const;

private:
    unsigned int _MaxCountPerField;      //< Default: 100
    unsigned int _WindowSize;            //< Default: 800
    unsigned int _GridSize;              //< Default: 50
    unsigned int _MaxTurnCount;          //< Default: 1000
    unsigned int _TurnDurationInMs;      //< Default: 50
    sf::Color    _BackgroundColor;       //< Default: Black
    std::string  _FontPath;              //< Default: "arial.ttf"
    bool         _PauseOnStartup;        //< Default: false
    bool         _IncreasingSplitValues; //< Default: true

};

#endif
