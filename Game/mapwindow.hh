#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMediaPlayer>
#include <math.h>
#include <iostream>
#include "map.h"
#include "startdialog.h"
#include "../CourseLib/interfaces/igameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gamemapgenerator.h"

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void initMap();
    int tileSize;
    int mapWidth;
    int mapHeight;
    Game::Map* gameMap;
    std::shared_ptr<Game::GameObjectManager> objManager;
    std::shared_ptr<Game::GameEventHandler> eventHandler;
    std::shared_ptr<Game::GameMapGenerator> mapCreator;

private slots:
    void on_quitButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MapWindow* m_ui;
    startDialog* startingDialog;

};

#endif // MapWINDOW_HH

