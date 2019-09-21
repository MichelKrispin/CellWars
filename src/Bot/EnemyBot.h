#ifndef _ENEMYBOT_H
#define _ENEMYBOT_H
#include "Bot/Bot.h"

/**
 * \brief The basic enemy class.
 *
 * This class can be extended to make some default enemies.
 */
class EnemyBot : public Bot

{
public:
    EnemyBot();
    virtual ~EnemyBot();

    /**
     * \brief The function which will be called on every turn.
     *
     * Should be overwritten for every new enemy.
     *
     * \param Snapshot A snapshot of the world at this moment.
     */
    virtual void MakeTurn(const WorldSnapshot& Snapshot) override;
};

#endif
