#include "gameframe.h"
#include "specialsort.h"
#include <QtWidgets>


/** The main frame where all happens. */
GameFrame::GameFrame()
{
    /** Create the top menu. */
    createMenu();

    /** Create a new game arena. */
    arena = new Arena;

    /** Create a new gridlayout as a main layout. */
    QGridLayout *mainLayout = new QGridLayout;

    /** Set the minimum size for the game arena. */
    arena->setMinimumSize(800,600);

    /** Widgets to layout. */
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(arena, 0, 0, 4, 3);

     /** Set the layout. */
    setLayout(mainLayout);
}

/** The destructor. */
GameFrame::~GameFrame()
{
    //qDebug() << "GAMEFRAME_deleted";
}

/** Create the menu here. */
void GameFrame::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    scoreAction = fileMenu->addAction(tr("High&score"));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    optionsMenu = new QMenu(tr("&Options"), this);
    generateAction = optionsMenu->addAction(tr("Generate a new &game"));
    menuBar->addMenu(optionsMenu);

    helpMenu = new QMenu(tr("&Help"), this);
    aboutAction = helpMenu->addAction(tr("&About"));
    manualAction = helpMenu->addAction(tr("&Manual"));
    menuBar->addMenu(helpMenu);

    connect(scoreAction, SIGNAL(triggered()), this, SLOT(showScore()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    connect(generateAction, SIGNAL(triggered()), this, SLOT(setMap()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(manualAction, SIGNAL(triggered()), this, SLOT(showManual()));
}

/** Show the help dialog. */
void GameFrame::showScore()
{
    QFile file("highscore.txt");
    highscore.clear();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);

    while ( !in.atEnd() )
    {
        QString line = in.readLine();
        highscore.append(line);
    }

    if (highscore.length() < 5)
    {
         while (highscore.length() <= 5)
         {
            highscore.append("line");
         }
    }

    qSort(highscore.begin(), highscore.end(), specialSort<QString>() );

    QMessageBox *dialog = new QMessageBox;

    dialog->setWindowTitle(" ");
    dialog->setContentsMargins(0,0,32,0);

    dialog->setText("<p><strong>A Few Greatest Darkfield Adventurers</strong></p>"
                    "<hr>"
                    "<p><h1>1. </h1>" + highscore[0].replace('|', ' ') + "</p>"
                    "<hr>"
                    "<p><h1>2. </h1>" + highscore[1].replace('|', ' ') + "</p>"
                    "<hr>"
                    "<p><h1>3. </h1>" + highscore[2].replace('|', ' ') + "</p>"
                    "<hr>"
                   );

    dialog->exec();
}

/** Generate a new game/map. */
void GameFrame::setMap()
{
    //qDebug() << " MAP CLICK RECEIVED!";

    arena->gameTrue = true;
    arena->player->alive = true;
    arena->player->randompos();

    for (int i = 1; i < ENEMIES+1; i++)
    {
        arena->enemies[i]->alive = true;
        arena->enemies[i]->setHitPoints();
        arena->enemies[i]->erandompos();
    }

    arena->populateMap();

    for (int i = 0; i < ROOMS; i++)
    {
        arena->makeRoom();
    }

    arena->makeWalls();

    arena->turn = -1;
    arena->player->hp = 5;
    arena->player->mp = 11;
    arena->player->level = 1;
    arena->player->gold = 0;
    arena->itemTimerS = 0;
    arena->itemTimerT = 0;

    arena->score = 0;
    arena->oldLevel = 1;
    arena->player->enemiesKilled = 0;

    arena->gameTurn();
    arena->repaint();
}

/** Show the help dialog. */
void GameFrame::showAbout()
{
    //qDebug() << " ABOUT DIALOG CREATED!";
    QMessageBox *dialog = new QMessageBox;

    dialog->setWindowTitle(" ");

    dialog->setContentsMargins(0,0,32,0);

    dialog->setText("<p><strong>About Darkfield</strong></p>"
                    "<hr>"
                    "<p>Version : 1.00</p>"
                    "<p>Author : Janne Kähkönen</p>"
                    "<hr>"
                    "<p>In Darkfield you explore the field where some strange creatures wonder around."
                    "They will not attack you straight away though."
                    "You may gain some experience from killing the creatures."
                    "<p>You also have a funny desire for digging up some treasures.</p>"
                    "<hr>"
                    "<p>The final aim is to dig up 10 treasures. "
                    "After those are found you also have to dig up the last one to finish the game.</p>"
                    "<hr>"
                    );

    dialog->exec();
}

void GameFrame::showManual()
{
    //qDebug() << " HELP DIALOG CREATED!";
    QMessageBox *dialog = new QMessageBox;

    dialog->setWindowTitle(" ");

    dialog->setContentsMargins(0,0,32,0);

    dialog->setText("<p><strong>The Darkfield Manual</strong></p>"
                    "<hr>"
                    "<p>On the top right you can see the game statistics:</p>"
                    "<p>The current turn (DAY), the hit points (HP), the move points (MP), "
                    "the current level (XP) and your money (GOLD).</p>"
                    "<hr>"
                    "<p>Move the player with the keypad on the middle right.</p>"
                    "<p>Use the rest button for resting and the dig button for digging.</p>"
                    "<hr>"
                    "<p>The screen on the bottom right tells you what is going on.</p>"
                    "<hr>"
                    "<p>On turn is equal to one day.</p>"
                    "<p>Every move or an action takes away one move point (MP).</p>"
                    "<p>Move points can be regained by resting.</p>"
                    "<hr>");

    dialog->exec();
}
