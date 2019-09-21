#ifndef _ENEMYBOT_H
#define _ENEMYBOT_H
#include "Bot.h"

class EnemyBot : public Bot
{
public:
    EnemyBot();
    virtual ~EnemyBot();

    virtual void MakeTurn(const WorldSnapshot& Snapshot) override;
};

#endif
