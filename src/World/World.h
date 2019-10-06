#ifndef _WORLD_H
#define _WORLD_H
#include "Bot/Bot.h"
#include "Renderer/Window.h"
#include "Grid.h"
#include "Bot/PlayerBot.h"

namespace sf { class Clock; }
class FieldList;
class WorldSnapshot;

/**
 * \mainpage Cell Wars 
 *
 * \section intro_sec Introduction
 *
 * This could be an introduction.
 * https://github.com/MichelKrispin/CellWars
 *
 * \section install_sec Installation
 *
 * Dependencies
 * You need git installed and CMake installed.
 * The Build scripts will download the needed git repositories.
 * (The project needs SFML to run correctly.)
 *
 * Using either the Build.sh or Build.bat script will build the project.
 */

/**
 * \brief Global world class which handles everything.
 *
 * The world class will play the game and be responsible for making every turn.
 * It also passes the updated FieldList on to the Window class which renders all fields.
 */
class World 
{
public:
    /**
     * \brief Returns a globally unique World.
     *
     * Usage as
     * \code{.cpp}
     * World& GameWorld = World::getWorld();
     * \endcode
     *
     * \return World World reference.
     */
    static World &GetWorld();

    /**
     * \brief Play the game.
     * Starts the game with two bots of which the game will be simulated.
     * Both bots will have to have different starting positions
     * as well as different teams. Otherwise the game will quit immediately.
     *
     * \param Player1 A pointer to a PlayerBot.
     * \param Player2 A pointer to another PlayerBot.
     */
    void Play(PlayerBot* Player1, PlayerBot* Player2);

    /**
     * \brief Play the game.
     * 
     * Starts the game with up to four bots of which the game will be simulated.
     * 
     * \param Bots A pointer to the pointers of bots.
     */
    void Play(Bot** Bots);

    // Used for the singleton pattern
    // Delete the copy and the assignment constructor
    World(const World&) = delete;
    World& operator=(const World&) = delete;

private:
    /**
     * \brief Initializes the World with a working window and fields.
     * Will be called on the first getWorld call.
     */
    World();
    virtual ~World();

    // Functions
    /**
     * \brief Update the world by calculating the actions of the field.
     */
    void _UpdateWorld();

    /**
     * \brief Render the world by passing everything needed to the renderer.
     *
     * \param TurnNumber The count of turns.
     *
     * \return Returns true if the window was killed while updating.
     */
    bool _RenderWorld(const unsigned int &TurnNumber);

    /**
     * \brief Saves the input Bots array to the local _Bots array.
     * 
     * \param Bots The input Bots array of all player.
     * 
     * \return Returns false if there is only one bot.
     */
    bool _SetInputToLocalBots(Bot** Bots);
     
    /**
     * \brief Initializes the world with the needed resources.
     * 
     * Mostly kept in a separate method for cleaner code.
     * This function uses the local _Bots array to initialize everything
     * so it doesn't need any new input.
     * 
     * \return Returns false if there is anything wrong in the initalization process.
     */
    bool _Initialize();

    // Variables
    Window _Window;                //< The window used to render everything on screen.
    Grid _Grid;                    //< The grid which keeps track of all fields in a more natural way.
    WorldSnapshot* _WorldSnapshot; //< A snapshot of the world which will be updated after each turn.
    FieldList* _Fields;            //< Keeping track of all fields for both teams.
    Bot* _Bots[4];                 //< An array of up to four Bot pointer. These are the playing bots.
    unsigned char _NumberOfBots;   //< The number of bots that are currently playing.
    sf::Clock* _Clock;             //< Used to measure the time between each turn.
};

#endif
