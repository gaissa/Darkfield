#include "player.h"
#include "arena.h"
#include <QtWidgets>

/** The constructor. */
Player::Player()
{    
    /** Set random position for the player. */
    randompos();

    /** Set the player char. */
    playerChar = '@';

    /** Set the player starting level. */
    level = 1;

    /** Set the player starting gold level. */
    gold = 0;

    /** Set the enemies killed count. */
    enemiesKilled = 0;

    /** Set the player alive. */
    alive = true;

    /** Set move points. */
    mp = 10;

    /** Set hit points. */
    hp = 5;
}

/** The destructor. */
Player::~Player()
{
    //qDebug() << "PLAYER_deleted";
}

/** Random number between low and high */
int Player::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

/** Sets a random position to the player */
void Player::randompos()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QThread::msleep(10);

    int p = randInt(2,WIDTH-2);

    int p2 = randInt(2,HEIGHT-2);

    pX = p;
    pY = p2;
}