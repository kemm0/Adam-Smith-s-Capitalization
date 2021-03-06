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
#include <QMessageBox>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ruleswindow.h"
#include "pricewindow.h"
#include "map.h"
#include "startdialog.h"
#include "../CourseLib/interfaces/igameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gamemapgenerator.h"
#include "gameresourcemap.h"


namespace Ui {
class MapWindow;
}

namespace Game{
/**
 * @brief The MapWindow class game window where is map, buttons and messageboxes
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow() override;

    /**
     * @brief resizeEvent handles events where user changes the mapwindow's size
     * @param event
     */
    void resizeEvent(QResizeEvent* event) override;
    /**
     * @brief showEvent is called when mapwindow show up on the screen
     * @param event
     */
    void showEvent(QShowEvent* event) override;
    /**
     * @brief getUsername used to get username from starting dialog to the game
     * @return
     */
    std::string getUsername();

    /**
     * @brief keyPressEvent handles events where user presses a key on keyboard
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief markHighScore
     * @param username
     * @param score
     * saves the current score to highscores.txt if it's better than the
     *  previous one or if there is no score with the given name
     */
    void markHighScore(std::string username, int score);



private slots:
    /**
     * @brief showGameMessage prints messages to textbox
     * @param message
     */
    void showGameMessage(std::string message);
    /**
     * @brief on_quitButton_clicked stops program
     */
    void on_quitButton_clicked();
    /**
     * @brief on_diceButton_clicked throws dice
     */
    void on_diceButton_clicked();
    /**
     * @brief on_endTurnButton_clicked resets all buttons
     */
    void on_endTurnButton_clicked();
    /**
     * @brief setUsername
     * @param username
     * stores the username given in startdialog
     */
    void setUsername(std::string username);
    /**
     * @brief on_moveButton_toggled if dice is thrown, lets player move
     * @param checked
     */
    void on_moveButton_toggled(bool checked);
    /**
     * @brief zoomIn
     * scales the graphicsview by 1.1
     */
    void zoomIn();
    /**
     * @brief zoomOut
     * scales the graphicsview by 0.9
     */
    void zoomOut();
    /**
     * @brief on_buildButton_toggled lets player built houses
     * @param checked
     */
    void on_buildButton_toggled(bool checked);
    /**
     * @brief on_searchAreaButton_toggled lets player search
     * @param checked
     */
    void on_searchAreaButton_toggled(bool checked);
    /**
     * @brief on_hireButton_toggled lets player hire workers
     * @param checked
     */
    void on_hireButton_toggled(bool checked);
    /**
     * @brief on_hiringList_currentIndexChanged
     * @param type type of worker chosen
     */
    void on_hiringList_currentIndexChanged(const QString &type);
    /**
     * @brief on_rulesButton_clicked Opens rules window and backstory
     */
    void on_rulesButton_clicked();
    /**
     * @brief gameOver opens pop window displaying different messages
     * @param ranOutOfMoney if player went bankcruptcy
     */
    void gameOver(gameOverState state);
    /**
     * @brief updateMoneyLabel
     */
    void updateMoneyLabel(int amount);
    /**
     * @brief on_pricesButton_clicked
     * opens up a window that shows prices
     */
    void on_pricesButton_clicked();

private:
    int tileSize;
    int mapWidth;
    int mapHeight;
    std::shared_ptr<Game::GameObjectManager> objManager;
    std::shared_ptr<Game::GameEventHandler> eventHandler;
    std::shared_ptr<Game::GameMapGenerator> mapCreator;
    Game::Map* gameMap;
    std::string username;
    Ui::MapWindow* m_ui;
    startDialog* startingDialog;
    QMediaPlayer* musicplayer;
    QMediaPlayer* soundEffectPlayer;
    QMediaPlaylist* musicPlaylist;
    PriceWindow *prices;
    rulesWindow *rules;

    /**
     * @brief lock_and_unlock_other_buttons locks other buttons when one button
     *  is pressed and releases them if toggle = false
     * @param toggle
     */
    void lock_and_unlock_other_buttons(bool toggle);
    /**
     * @brief buttons_update locks button if ongoing action or action has been
     * made in turn
     */
    void buttons_update();

    /**
     * @brief treasureFoundSound
     * played on finding a treasure
     */
    void treasureFoundSound();
    /**
     * @brief robberFoundSound
     * played on encountering a robber
     */
    void robberFoundSound();
    /**
     * @brief nothingFoundSound
     * played when the searched tile is empty
     */
    void nothingFoundSound();
    /**
     * @brief buildSound
     * played on building a new building
     */
    void buildSound();

};
}

#endif // MapWINDOW_HH

