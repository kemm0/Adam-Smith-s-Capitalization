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
#include "map.h"
#include "startdialog.h"
#include "../CourseLib/interfaces/igameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"

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
    int tileSize;
    int mapWidth;
    int mapHeight;
    Map* gameMap;
    GameObjectManager* a = new GameObjectManager();
    std::shared_ptr<GameObjectManager> objManager;
    std::shared_ptr<GameEventHandler> eventHandler;

private slots:
    void on_quitButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MapWindow* m_ui;
    startDialog* startingDialog;

};

#endif // MapWINDOW_HH

