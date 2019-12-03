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
#include "QMessageBox"


namespace Ui {
class MapWindow;
}

namespace Game{
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
    Game::Map* gameMap;
    std::string username;
    std::shared_ptr<Game::GameObjectManager> objManager;
    std::shared_ptr<Game::GameEventHandler> eventHandler;
    std::shared_ptr<Game::GameMapGenerator> mapCreator;
    QMediaPlayer* musicplayer;
    QMediaPlayer* soundEffectPlayer;
    QMediaPlaylist* musicPlaylist;
    std::string getUsername();
    void keyPressEvent(QKeyEvent *event) override;


private slots:
    void showGameMessage(std::string message);
    void on_quitButton_clicked();

    void on_diceButton_clicked();

    void on_endTurnButton_clicked();
    void setUsername(std::string username);

    void on_moveButton_toggled(bool checked);

    void zoomIn();
    void zoomOut();

    void on_buildButton_toggled(bool checked);
    void on_searchAreaButton_toggled(bool checked);

    void treasureFoundSound();
    void robberFoundSound();
    void nothingFoundSound();
    void buildSound();
    void showTileInfo(std::string info);

    void on_hireButton_toggled(bool checked);

    void on_hiringList_currentIndexChanged(const QString &arg1);

    void on_rulesButton_clicked();

    void gameOver(bool ranOutOfMoney);

private:
    Ui::MapWindow* m_ui;
    startDialog* startingDialog;
    void lock_and_unlock_other_buttons(bool toggle);
    void buttons_update();
    int maxTurns;



};
}

#endif // MapWINDOW_HH

