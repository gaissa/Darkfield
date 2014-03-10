#include "enemy.h"
#include "qdebug.h"
#include "arena.h"
#include <QtWidgets>


/** The constructor. */
Enemy::Enemy()
{
    erandompos();
    setHitPoints();

    /** Set the enemy char. */
    enemyChar = 'H';

    // Set alive.
    alive = true;
}

/** The destructor. */
Enemy::~Enemy()
{
    //qDebug() << "ENEMY_deleted";
}

/** Random number between low and high */
int Enemy::randInt(int low, int high)
{    
    return qrand() % ((high + 1) - low) + low;
}

/** Sets a random position for the enemy */
void Enemy::erandompos()
{
    int e = randInt(2,WIDTH-2);
    int e2 = randInt(2,HEIGHT-2);

    eX = e;
    eY = e2;
}

/** Sets a the hitpoints for the enemy. */
void Enemy::setHitPoints()
{
    ehp = randInt(1,10);
}
