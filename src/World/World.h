#ifndef _WORLD_H
#define _WORLD_H
#include "Bot/Bot.h"
#include "Renderer/Window.h"
#include "FieldList.h"
#include "Grid.h"
#include "WorldSnapshot.h"
#include "Bot/EnemyBot.h"
#include "Bot/PlayerBot.h"
#include <SFML/System/Clock.hpp>

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
    static World &getWorld();

    /**
     * \brief Play the game.
     * Starts the game with two bots of which the game will be simulated.
     * The Player will be blue while the Enemy is in red color.
     *
     * \Param Player A pointer to a PlayerBot.
     * \Param Enemy  A pointer to an EnemyBot.
     */
    void Play(PlayerBot* Player, EnemyBot* Enemy);

    /**
     * \brief Play the game.
     * Starts the game with two bots of which the game will be simulated.
     *
     * \Param Blue A pointer to the first bot.
     * \Param Red A pointer to the second bot.
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
     *
     * \return Returns true if the window was killed while updating
     */
    bool UpdateWorld();
     

    // Variables
    Window _Window;                //< The window used to render everything on screen.
    Grid _Grid;                    //< The grid which keeps track of all fields in a more natural way.
    WorldSnapshot* _WorldSnapshot; //< A snapshot of the world which will be updated after each turn.
    FieldList* _Fields;            //< Keeping track of all fields for both teams.
    sf::Clock _Clock;              //< Used to measure the time between each turn.
};

#endif
