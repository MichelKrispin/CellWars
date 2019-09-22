#ifndef _WORLD_H
#define _WORLD_H
#include "Bot/Bot.h"
#include "Renderer/Window.h"
#include "Grid.h"
#include "Bot/EnemyBot.h"
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
     * The Player will be blue while the Enemy is in red color.
     *
     * \param Player A pointer to a PlayerBot.
     * \param Enemy  A pointer to an EnemyBot.
     */
    void Play(PlayerBot* Player, EnemyBot* Enemy);

    /**
     * \brief Play the game.
     * Starts the game with two bots of which the game will be simulated.
     *
     * \param Blue A pointer to the first bot.
     * \param Red A pointer to the second bot.
     */
    void Play(Bot* Blue, Bot* Red);

private:
    /**
     * \brief Initializes the World with a working window and fields.
     * Will be called on the first getWorld call.
     */
    World();
    virtual ~World();

    // Used for the singleton pattern
    // Delete the copy and the assignment constructor
    World(const World&) = delete;
    World& operator=(const World&) = delete;


    // Functions
    /**
     * \brief Update the world by calculating the actions of the field.
     */
    void _UpdateWorld();

    /**
     * \brief Render the world by passing everything needed to the renderer.
     *
     * \return Returns true if the window was killed while updating.
     */
    bool _RenderWorld();

    /**
     * \brief Initializes the world with the needed resources.
     * Mostly kept in a separate method for cleaner code.
     *
     * \param Blue Just transfering the pointer from the Play function.
     * \param Red Just transfering the pointer from the Play function.
     */
    void _Initialize(Bot* Blue, Bot* Red);
     

    // Variables
    Window _Window;                //< The window used to render everything on screen.
    Grid _Grid;                    //< The grid which keeps track of all fields in a more natural way.
    // TODO: Make multiple snapshots (one for each team)
    WorldSnapshot* _WorldSnapshot; //< A snapshot of the world which will be updated after each turn.
    FieldList* _Fields;            //< Keeping track of all fields for both teams.
    sf::Clock* _Clock;             //< Used to measure the time between each turn.
};

#endif
