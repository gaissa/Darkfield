#ifndef Arena_H
#define Arena_H


#include <QWidget>
#include "qpainter.h"
#include "player.h"
#include "enemy.h"


#define WIDTH 71
#define HEIGHT 38
#define FOV 4
#define ENEMIES 50
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

    Enemy *enem01, *enem02, *enem03, *enem04, *enem05,
          *enem06, *enem07, *enem08, *enem09, *enem10,
          *enem11, *enem12, *enem13, *enem14, *enem15,
          *enem16, *enem17, *enem18, *enem19, *enem20,
          *enem21, *enem22, *enem23, *enem24, *enem25,
          *enem26, *enem27, *enem28, *enem29, *enem30,
          *enem31, *enem32, *enem33, *enem34, *enem35,
          *enem36, *enem37, *enem38, *enem39, *enem40,
          *enem41, *enem42, *enem43, *enem44, *enem45,
          *enem46, *enem47, *enem48, *enem49, *enem50;          

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