#include "mapwindow.hh"

#include <QApplication>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    Game::MapWindow mapWindow;
    mapWindow.show();
    return app.exec();
}
