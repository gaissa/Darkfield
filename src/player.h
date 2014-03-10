#ifndef PLAYER_H
#define PLAYER_H


class Player
{

public:
    Player();
    ~Player();

    bool alive;

    int pX, pY;

    int mp;
    int hp;
    int gold;

    char playerChar;

    int level;

    int enemiesKilled;

    void randompos();

private:
     int randInt(int low, int high);
};

#endif // PLAYER_H