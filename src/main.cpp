#include "gameframe.h"
#include <QApplication>


/** Create and run the main app. */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameFrame gameframe;

    gameframe.setWindowFlags(gameframe.windowFlags() | Qt::WindowMinimizeButtonHint);

    gameframe.setWindowTitle("Darkfield");

    gameframe.setMaximumSize(822,643);
    gameframe.show();

    return app.exec();
}
