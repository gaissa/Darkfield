#include "arena.h"
#include "ui_arena.h"
#include "qdebug.h"
#include <QtWidgets>


/** The game arena */
Arena::Arena(QWidget *parent) :
             QWidget(parent),
             ui(new Ui::Arena)
{
    /** Set the ui. */
    ui->setupUi(this);

    /** The game is on. */
    gameTrue = true;

    /** Turn is 0. */
    turn = 0;

    /** The player level is 1. */
    oldLevel = 1;

    /** Create the player. */
    player = new Player;

    /** Create the enemies */
    for (int e = 1; e < ENEMIES+1; e++)
    {
        enemies[e] = new Enemy();
    }

    /** Get the fonts which are FixedPitch type. */
    QFontDatabase database;

    /** Create font object. */
    QFont font;

    /** Set the FixedPitch font. */
    foreach (QString family, database.families())
    {
        if (database.isFixedPitch(family))
        {
            font = QFont(family);
            break;
        }
    }

    /** Set the font size. */
    font.setPointSize(11);

    /** Set the font. */
    setFont(font);
}

/** The destructor */
Arena::~Arena()
{
    delete ui;
    delete player;

    for (int e = 1; e < ENEMIES+1; e++)
    {
        delete enemies[e];
    }
    delete enemies;

    //qDebug() << "ARENA_deleted";
}

/** Draw the game area here. */
void Arena::paintEvent(QPaintEvent *)
{
    /** Just to check if the game is on. */
    if (gameTrue)
    {
        /** The painter object to this event. */
        QPainter painter(this);

        /** Get the font size from char and set it. */
        QFontMetrics metrics(font());
        int fontWidth = metrics.width('X');
        int fontHeight = metrics.height();

        /** the QPoint position. */
        int yPos = fontHeight;
        int xPos;

        /** Draw a filled rectangle (arena background). */
        painter.fillRect(rect(), Qt::black);

        /** Loop through the map and color the objects Y. */
        for (int y = 0; y < HEIGHT; y++)
        {
            yPos += fontHeight;
            xPos = 0;

            /** Loop through the map and color the objects X. */
            for (int x = 0; x < WIDTH; x++)
            {
                if ( (map[(x)][(y)] == '#') )
                {
                    painter.setPen(Qt::gray);

                    if ((x > player->pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(QColor(30,30,30));
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(QColor(30,30,30));
                    }
                }
                else if ( (map[(x)][(y)] == '+') )
                {
                    painter.setPen(Qt::gray);

                    if ((x > player->pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                }
                else if (map[(x)][(y)] == 'A')
                {
                    painter.setPen(Qt::green);

                    if ((x >player-> pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                }
                else if (map[(x)][(y)] == '*')
                {
                    painter.setPen(Qt::cyan);

                    if ((x > player->pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                }
                else if (map[(x)][(y)] == '8')
                {
                    painter.setPen(Qt::yellow);

                    if ((x > player->pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                }
                else if (map[(x)][(y)] == '.')
                {
                    painter.setPen(QColor(60,90,60));

                    if ((x > player->pX + FOV) || (x < player->pX-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                    if ((y > player->pY + FOV) || (y < player->pY-FOV))
                    {
                        painter.setPen(Qt::black);
                    }
                }

                /** draw the objects; */
                painter.drawText(QPoint(xPos, yPos), (map[x][y]));
                xPos += fontWidth;
            }
        }

        /** Draw the player on map. */
        if (player->alive == true)
        {
            painter.setPen(Qt::white);
            painter.drawText(QPoint(player->pX * fontWidth, (player->pY + 2) * fontHeight), QChar(player->playerChar));
        }

        /** Draw the common enemy on map if near enough and alive. */
        for (int e = 1; e < ENEMIES+1; e++)
        {
            if (enemies[e]->alive == true)
            {
                /** set FOV color for enemy. */
                painter.setPen(Qt::black);

                for (int i = 1; i <= FOV; i++)
                {
                    for (int j = 0; j <= FOV; j++)
                    {
                        if ( (player->pX + i == enemies[e]->eX || player->pX - i == enemies[e]->eX) && (player->pY+j == enemies[e]->eY) )
                        {
                            painter.setPen(Qt::red);
                        }
                        if ( (player->pX + i == enemies[e]->eX || player->pX - i == enemies[e]->eX) && (player->pY-j == enemies[e]->eY) )
                        {
                            painter.setPen(Qt::red);
                        }
                        if ( (player->pY + i == enemies[e]->eY || player->pY - i == enemies[e]->eY) && (player->pX == enemies[e]->eX) )
                        {
                            painter.setPen(Qt::red);
                        }
                    }
                }

                /** Draw the enemy. */
                painter.drawText(QPoint(enemies[e]->eX * fontWidth, (enemies[e]->eY + 2) * fontHeight), QChar(enemies[e]->enemyChar));
            }
        }
    }
}

/** Fighting happens here. */
void Arena::fightEnemies()
{
    int i = 1;

    while (i < ENEMIES+1)
    {
        if (player->pX == enemies[i]->eX && player->pY == enemies[i]->eY)
        {
            if (enemies[i]->ehp < player->hp)
            {
                enemies[i]->alive = false;
                player->enemiesKilled++;
                ui->label_5->setStyleSheet("QLabel { background-color : black; color : white; border: 2px solid #222; }");
                ui->label_5->setText("You kill an enemy!");
                success = true;
            }
            else
            {
                if (player->hp > 1)
                {
                    player->hp--;

                    ui->label_5->setStyleSheet("QLabel { background-color : black; color : purple; border: 2px solid #222; }");
                    ui->label_5->setText("The enemy hits you! Escape and regain some strength!");
                    success = true;

                    break;
                }
                else
                {
                    score = ( ( (player->level * 100) - (turn - player->hp) ) * player->gold+1);

                    QFile file("highscore.txt");

                    if (!file.open(QIODevice::Append | QIODevice::Text))
                    {
                        return;
                    }

                    player->alive = false;

                    ui->label_15->setStyleSheet("QLabel { background-color : black; color : red; border: 2px solid #222; }");
                    ui->label_15->setText("You are dead!");

                    ui->groupBox->show();

                    repaint();

                    QTextStream out(&file);
                    out << "NAME: " << name << " - TIME: " << turn << " DAYS" << " - LEVEL: " << "" << player->level << " - SCORE: " << "|" << score << "\n";

                    break;
                }
            }
        }
        i++;
    }

    QString hpString = QString::number(player->hp);
    ui->label_4->setText(hpString);
}

/** Random number between low and high */
int Arena::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

/** Draw the map and populate it with objects. */
void Arena::populateMap()
{
    for (int x = 1; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            /** Create the trees. */
            if(qrand() % 20 == 0 )
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = 'A';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }

            /** Create the shrines. */
            else if(qrand() % 675 == 0 )
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '*';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }

            /** Create the totem poles. */
            else if(qrand() % 675 == 0 )
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '8';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }
            else
            {
                map[x][y] = '.';
            }
        }
    }
}

/** Draw the rooms on the map */
void Arena::makeRoom()
{
    int a = randInt(8,WIDTH-2);
    int b = randInt(2,HEIGHT-32);
    int c = randInt(8,HEIGHT-2);

    for (int x = 1; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            /** Make the left wall. */
            if (x == a/2 && y < c-1 && y > b+1)
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '+';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }
            /** Make the right wall */
            else if (x == a && y < c-1 && y > b+1)
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '+';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }
            /** Make the top wall. */
            else if (y == b && x > (a/2)-1 && x <= a)
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '+';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }
            /** Make the bottom wall. */
            else if (y == c && x > (a/2)-1 && x <= a)
            {
                int ab = 1;

                while (ab < ENEMIES+1)
                {
                    if ( (x != player->pX || y != player->pY) && (x != enemies[ab]->eX || y != enemies[ab]->eY) )
                    {
                        map[x][y] = '+';
                    }
                    else
                    {
                        map[x][y] = '.';
                        break;
                    }
                    ab++;
                }
            }
        }
    }
}

/** Make the main walls of the game field. */
void Arena::makeWalls()
{
    for (int x = 1; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            if (x == 1 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
            {
                map[x][y] = '#';
            }
        }
    }
}

/** Do this stuff every turn. */
void Arena::gameTurn()
{    
    success = false;

    ui->label_5->setStyleSheet("QLabel { background-color : black; color : #696969; border: 2px solid #222; }");

    /** Move the enemies. */
    moveEnemy();

    /** Fight the enemies. */
    fightEnemies();

    /** Increment the turn. */
    turn++;

    itemTimerS++;
    itemTimerT++;

    QString dayString = QString::number(turn);
    ui->label_3->setText(dayString);

    if (player->hp < 1)
    {
        score = ( ( (player->level * 100) - (turn - player->hp) ) * (player->gold+1) );

        QFile file("highscore.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return;
        }

        player->alive = false;

        //gameTrue = false;

        ui->label_15->setStyleSheet("QLabel { background-color : black; color : red; border: 2px solid #222; }");
        ui->label_15->setText("You are dead!");
        ui->groupBox->show();

        repaint();

        QTextStream out(&file);
        out << "NAME: " << name << " - TIME: " << turn << " DAYS" << " - LEVEL: " <<  player->level << " - GOLD: " << player->gold << " - SCORE: " << "|" << score << "\n";
    }
    if (player->gold > 10)
    {
        score = ( ( (player->level * 100) - (turn - player->hp) ) * (player->gold+1) );

        QFile file("highscore.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return;
        }

        ui->label_15->setStyleSheet("QLabel { background-color : black; color : green; border: 2px solid #222; }");
        ui->label_15->setText("You find all the treasure there is!");
        ui->groupBox->show();

        repaint();

        QTextStream out(&file);
        out << "NAME: " << name << " - TOTAL PLAYTIME: " << turn << " DAYS" << " - LEVEL: " <<  player->level << " - GOLD: " << player->gold << " - SCORE: " << "|" << score << "\n";
    }
    if (player->mp > 0)
    {
        player->mp--;
        QString mpString = QString::number(player->mp);
        ui->label_7->setText(mpString);
    }
    if (player->enemiesKilled == 2 && oldLevel == 1)
    {
        oldLevel++;
        player->level++;
        QString ekString = QString::number(player->level);
        ui->label_8->setText(ekString);
        ui->label_5->setStyleSheet("QLabel { background-color : lime; color : black; border: 2px solid #222; }");
        ui->label_5->setText("You level up!");
    }
    if (player->enemiesKilled == 4 && oldLevel == 2)
    {
        oldLevel++;
        player->level++;
        QString ekString = QString::number(player->level);
        ui->label_8->setText(ekString);
        ui->label_5->setStyleSheet("QLabel { background-color : lime; color : black; border: 2px solid #222; }");
        ui->label_5->setText("You level up!");
    }
    if (player->enemiesKilled == 6 && oldLevel == 3)
    {
        oldLevel++;
        player->level++;
        QString ekString = QString::number(player->level);
        ui->label_8->setText(ekString);
        ui->label_5->setStyleSheet("QLabel { background-color : lime; color : black; border: 2px solid #222; }");
        ui->label_5->setText("You level up!");
    }
    if (player->enemiesKilled == 8 && oldLevel == 4)
    {
        oldLevel++;
        player->level++;
        QString ekString = QString::number(player->level);
        ui->label_8->setText(ekString);
        ui->label_5->setStyleSheet("QLabel { background-color : lime; color : black; border: 2px solid #222; }");
        ui->label_5->setText("You level up!");
    }
    if (player->enemiesKilled == 10 && oldLevel == 5)
    {
        oldLevel++;
        player->level++;
        QString ekString = QString::number(player->level);
        ui->label_8->setText(ekString);
        ui->label_5->setStyleSheet("QLabel { background-color : lime; color : black; border: 2px solid #222; }");
        ui->label_5->setText("You level up!");
    }
    if ((map[player->pX][player->pY-1] == '*') ||
        (map[player->pX+1][player->pY-1] == '*') ||
        (map[player->pX+1][player->pY] == '*') ||
        (map[player->pX+1][player->pY+1] == '*') ||
        (map[player->pX][player->pY+1] == '*') ||
        (map[player->pX-1][player->pY+1] == '*') ||
        (map[player->pX-1][player->pY] == '*') ||
        (map[player->pX-1][player->pY-1] == '*'))
    {
        if ( (itemTimerS > 7) )
        {
            ui->label_5->setStyleSheet("QLabel { background-color : black; color : green; border: 2px solid #222; }");
            ui->label_5->setText("The SHRINE gives you +1 HP!");
            ++player->hp;

            QString hpString = QString::number(player->hp);
            ui->label_4->setText(hpString);

            itemTimerS = 0;
        }
        else
        {
            ui->label_5->setStyleSheet("QLabel { background-color : black; color : #696969; border: 2px solid #222; }");
            QString waitString = QString::number(8-itemTimerS);
            ui->label_5->setText("You have to wait " + waitString + "days.");
        }
    }
    else if ((map[player->pX][player->pY-1] == '8') ||
             (map[player->pX+1][player->pY-1] == '8') ||
             (map[player->pX+1][player->pY] == '8') ||
             (map[player->pX+1][player->pY+1] == '8') ||
             (map[player->pX][player->pY+1] == '8') ||
             (map[player->pX-1][player->pY+1] == '8') ||
             (map[player->pX-1][player->pY] == '8') ||
             (map[player->pX-1][player->pY-1] == '8'))
    {
        if ( (itemTimerT > 30) )
        {
            ui->label_5->setStyleSheet("QLabel { background-color : black; color : green; border: 2px solid #222; }");
            ui->label_5->setText("The TOTEM POLE gives you +3 HP!");
            player->hp = player->hp+3;

            QString hpString2 = QString::number(player->hp);
            ui->label_4->setText(hpString2);

            itemTimerT = 0;
        }
        else
        {
            ui->label_5->setStyleSheet("QLabel { background-color : black; color : #696969; border: 2px solid #222; }");
            QString waitString2 = QString::number(31-itemTimerT);
            ui->label_5->setText("You have to wait " + waitString2 + "days.");
        }
    }
    else if (player->alive == true && success == false)
    {
        ui->label_5->setText("Just darkness around you...");
    }

    QString goldString = QString::number(player->gold);
    ui->label_10->setText(goldString);

    repaint();
}

/** Move the enemies. */
void Arena::moveEnemy()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    const char arrayNum[3] = {0, -1, 1};

    for (int i = 1; i < ENEMIES+1; i++)
    {
        int RandIndex = rand() % 3;   // generates a random number between 0 and 2
        int RandIndex2 = rand() % 3;  // generates a random number between 0 and 2

        if ( (map[enemies[i]->eX+((arrayNum[RandIndex]))][enemies[i]->eY+((arrayNum[RandIndex2]))] == '.'))
        {
            enemies[i]->eX = enemies[i]->eX + (arrayNum[RandIndex]);
            enemies[i]->eY = enemies[i]->eY + (arrayNum[RandIndex2]);
        }
        else
        {
        }
    }
    //fightEnemies();
}

/** Button 1 NW */
void Arena::on_pushButton_1_clicked()
{
    if ((map[player->pX-1][player->pY-1] == '.') && (player->mp > 0))
    {
        player->pX--;
        player->pY--;
    }
    gameTurn();
    repaint();
}

/** Button 2 NORTH */
void Arena::on_pushButton_2_clicked()
{
    if ((map[player->pX][player->pY-1] == '.') && (player->mp > 0))
    {
        player->pY--;
    }
    gameTurn();
    repaint();
}

/** Button 3 NE */
void Arena::on_pushButton_3_clicked()
{
    if ((map[player->pX+1][player->pY-1] == '.') && (player->mp > 0))
    {
        player->pX++;
        player->pY--;
    }
    gameTurn();
    repaint();
}

/** Button 4 WEST*/
void Arena::on_pushButton_4_clicked()
{
    if ((map[player->pX-1][player->pY] == '.') && (player->mp > 0))
    {
        player->pX--;
    }
    gameTurn();
    repaint();
}

/** Button 6 EAST */
void Arena::on_pushButton_6_clicked()
{
    if ((map[player->pX+1][player->pY] == '.') && (player->mp > 0))
    {
        player->pX++;
    }
    gameTurn();
    repaint();
}

/** Button 7 SW */
void Arena::on_pushButton_7_clicked()
{
    if ((map[player->pX-1][player->pY+1] == '.') && (player->mp > 0))
    {
        player->pX--;
        player->pY++;
    }
    gameTurn();
    repaint();
}

/** Button 8 SOUTH */
void Arena::on_pushButton_8_clicked()
{
    if ((map[player->pX][player->pY+1] == '.') && (player->mp > 0))
    {
        player->pY++;
    }
    gameTurn();
    repaint();
}

/** Button 9 SE */
void Arena::on_pushButton_9_clicked()
{
    if ((map[player->pX+1][player->pY+1] == '.') && (player->mp > 0))
    {
        player->pX++;
        player->pY++;
    }
    gameTurn();
    repaint();
}

/** Button 5 ACTION */
void Arena::on_pushButton_5_clicked()
{
    int r = randInt(1,3);

    if ( (player->mp > 0) && (r == 1 || r == 2) )
    {
        map[player->pX][player->pY] = '*';
        player->hp = player->hp-3;

        gameTurn();

        ui->label_5->setStyleSheet("QLabel { background-color : black; color : orange; border: 2px solid #222; }");
        ui->label_5->setText("You hit a volcano and lose -3 HP.");
    }
    else if ( (player->mp > 0) && (r == 3) )
    {
        map[player->pX][player->pY] = '+';
        player->gold++;

        gameTurn();

        ui->label_5->setStyleSheet("QLabel { background-color : black; color : yellow; border: 2px solid #222; }");
        ui->label_5->setText("You hit a gold mine and dig it all up happily while gaining +1 GP.");
    }
    else if ( (player->mp < 1))
    {
        gameTurn();

        ui->label_5->setStyleSheet("QLabel { background-color : black; color : #696969; border: 2px solid #222; }");
        ui->label_5->setText("You do not have enough move points!");
    }
}

/** Button 10 REST */
void Arena::on_pushButton_10_clicked()
{
    moveEnemy();

    if (player->mp < 10)
    {
        ui->label_5->setStyleSheet("QLabel { background-color : black; color : lime; border: 2px solid #222; }");
        ui->label_5->setText("You have a little rest and gain +1 MP.");
        player->mp++;
        QString mpString = QString::number(player->mp);
        ui->label_7->setText(mpString);

        turn++;
        itemTimerS++;
        itemTimerT++;
        QString dayString = QString::number(turn);
        ui->label_3->setText(dayString);
    }
    else
    {
        ui->label_5->setStyleSheet("QLabel { background-color : black; color : #696969; border: 2px solid #222; }");
        ui->label_5->setText("Your MP are at the maximum!");
        turn++;
        itemTimerS++;
        itemTimerT++;
        QString dayString = QString::number(turn);
        ui->label_3->setText(dayString);
    }

    repaint();
}

/** Button 11 THE START BUTTON */
void Arena::on_pushButton_11_clicked()
{
    name = ui->textEdit->toPlainText();

    turn = 0;
    score = 0;
    oldLevel = 1;

    player->alive = true;
    player->enemiesKilled = 0;
    player->gold = 0;
    player->level = 1;
    player->mp = 11;
    player->hp = 5;
    itemTimerS = 0;
    itemTimerT = 0;

    delete player;

    for (int e = 1; e < ENEMIES+1; e++)
    {
        delete enemies[e];
    }

    /** Create the player. */
    player = new Player;

    /** Crate the enemies */
    for (int e = 1; e < ENEMIES+1; e++)
    {
        enemies[e] = new Enemy();
    }

    /** Draw the map and populate the objects on map. */
    populateMap();

    /** Draw the rooms on the map */
    for (int i = 0; i < ROOMS; i++)
    {
        this->makeRoom();
    }

    makeWalls();

    turn--;

    player->mp++;

    gameTurn();
}