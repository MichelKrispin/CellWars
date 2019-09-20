#ifndef _WORLD_H
#define _WORLD_H
#include "Bot.h"
#include "Window.h"
#include "FieldList.h"
#include "WorldSnapshot.h"

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
     */
    void UpdateWorld();
     

    // Variables
    Window _Window; //< The window used to render everything on screen.
    WorldSnapshot* _WorldSnapshot; //< A snapshot of the world which will be updated after each turn.
    FieldList* _Fields; //< Keeping track of all fields for both teams.
};

#endif
