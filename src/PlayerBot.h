#ifndef _PLAYERBOT_H
#define _PLAYERBOT_H
#include "Bot.h"

class PlayerBot : public Bot
{
public:
    PlayerBot();
    virtual ~PlayerBot();
    
    /**
     * \brief The turn function which should be overriden.
     *
     * This function will be called on every turn and will be called by the world.
     */
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override;
};

#endif
