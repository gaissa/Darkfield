#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{

public:
    Enemy();
    ~Enemy();

    //char enemyNum[3] = { 'H', 'B', 'C' };
    char enemyChar;

    int ehp;

    int eX, eY;

    void erandompos();

    void setHitPoints();

    bool alive;

private:
     int randInt(int low, int high);
};


#endif // ENEMY_H
