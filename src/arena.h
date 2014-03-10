#ifndef Arena_H
#define Arena_H


#include <QWidget>
#include "qpainter.h"
#include "player.h"
#include "enemy.h"


#define WIDTH 71
#define HEIGHT 38
#define FOV 4
#define ENEMIES 30
#define ROOMS 4


namespace Ui
{
    class Arena;
}

class Arena : public QWidget
{
    Q_OBJECT
    
public:
    explicit Arena(QWidget *parent = 0);
    ~Arena();

    bool gameTrue;

    int turn;

    int score;

    int oldLevel;

    int itemTimerS;
    int itemTimerT;

    Enemy *enemies[];
    Player *player;

    Enemy *enem;
    Enemy *enem2;
    Enemy *enem3;
    Enemy *enem4;
    Enemy *enem5;
    Enemy *enem6;
    Enemy *enem7;
    Enemy *enem8;
    Enemy *enem9;
    Enemy *enem10;
    Enemy *enem11;
    Enemy *enem12;
    Enemy *enem13;
    Enemy *enem14;
    Enemy *enem15;
    Enemy *enem16;
    Enemy *enem17;
    Enemy *enem18;
    Enemy *enem19;
    Enemy *enem20;
    Enemy *enem21;
    Enemy *enem22;
    Enemy *enem23;
    Enemy *enem24;
    Enemy *enem25;
    Enemy *enem26;
    Enemy *enem27;
    Enemy *enem28;
    Enemy *enem29;
    Enemy *enem30;

    void gameTurn();

    void populateMap();
    void makeRoom();
    void makeWalls();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Arena *ui;

    QChar map[WIDTH][HEIGHT];

    QString name;

    bool success;

    void moveEnemy();
    void fightEnemies();

    int randInt(int low, int high);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();
};

#endif // Arena_H