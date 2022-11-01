#include <QApplication>
#include <QGraphicsView>

#include "Game/game.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QGraphicsView view;
    Game* game = new Game(std::array<QBrush, 3> {Qt::yellow, Qt::red, Qt::green});
    view.setScene(game);
    view.show();
    return app.exec();
}