#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include <arena.h>


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMenuBar;
QT_END_NAMESPACE


class GameFrame : public QDialog
{
    Q_OBJECT

public:
    GameFrame();
    ~GameFrame();

private:
    void createMenu();

    QMenuBar *menuBar;

    QMenu *fileMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QAction *scoreAction;
    QAction *exitAction;
    QAction *generateAction;
    QAction *aboutAction;
    QAction *manualAction;

    Arena *arena;

    QStringList highscore;

private slots:
     void showScore();
     void showAbout();
     void showManual();
     void setMap();
};

#endif
