#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <iostream>
#include "QMediaPlaylist"

namespace Game{
MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow)
{
    //Start dialog
    startingDialog = new startDialog();
    connect(startingDialog,
            &startDialog::nameConfirmed,
            this,
            &MapWindow::setUsername);

    startingDialog->exec();

    m_ui->setupUi(this);
    setWindowIcon(QIcon(QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png")));
    setWindowTitle("Adam Smith's Capitalization");

    //initialize game components
    objManager = std::make_shared<Game::GameObjectManager>();
    eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    mapCreator = std::make_shared<Game::GameMapGenerator>(objManager,
                                                          eventHandler);

    //initialize game windows
    prices = new PriceWindow(this);
    prices->setWindowTitle("Prices");
    rules = new rulesWindow(this);
    rules->setWindowTitle("Game Info");
    showGameMessage(
                "Hello " + username + "! \n Get ready to conquer Pirkanmaa");
    updateMoneyLabel(objManager->getPlayer()->getResources().at(Course::MONEY));
    m_ui->MoneyTextLabel->setPixmap(QPixmap("../../juho-ja-leo/Game/Sprites/money.png"));

    //initialize map
    gameMap = new Game::Map(nullptr,eventHandler,objManager,mapCreator);
    gameMap->drawMap();
    gameMap->setFocus();
    m_ui->gameMapView->setScene(gameMap);
    m_ui->gameMapView->setMouseTracking(true);
    m_ui->gameMapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    gameMap->setBackgroundBrush(Qt::black);
    m_ui->gameMapView->scale(0.9,0.9);

    //initialize buttons
    m_ui->endTurnButton->setDisabled(false);
    m_ui->moveButton->setCheckable(true);
    m_ui->buildButton->setCheckable(true);
    m_ui->searchAreaButton->setCheckable(true);
    m_ui->hireButton->setCheckable(true);

    //Initialize music

    // self made with bandlab :D enjoy
    musicplayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist();

    musicPlaylist->addMedia(
                QUrl::fromLocalFile(
                    "../../juho-ja-leo/Game/Music/gamemusic.wav"));

    musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    musicplayer->setPlaylist(musicPlaylist);
    musicplayer->play();

    //Initialize sound effects

    //all sound effects are from freesounds.org
    //and have a license that allows free usage of the files
    soundEffectPlayer = new QMediaPlayer();
    connect(gameMap,&Map::robberFound,this,&MapWindow::robberFoundSound);
    connect(gameMap,&Map::treasureFound,this,&MapWindow::treasureFoundSound);
    connect(gameMap,&Map::nothingFound,this,&MapWindow::nothingFoundSound);
    connect(gameMap,&Map::built,this,&MapWindow::buildSound);

    // Connect signals and slots
    connect(gameMap,&Map::inspectTile,this,&MapWindow::showGameMessage);
    connect(mapCreator.get(),&GameMapGenerator::gameMessage,
            this,
            &MapWindow::showGameMessage);
    connect(eventHandler.get(),&GameEventHandler::gameMessage,
            this,&MapWindow::showGameMessage);
    connect(eventHandler.get(), &GameEventHandler::gameOver,
            this, &MapWindow::gameOver);
    connect(objManager->getPlayer().get(), &Player::currentMoney,
            this,&MapWindow::updateMoneyLabel);

}

MapWindow::~MapWindow()
{
    delete m_ui;
    delete soundEffectPlayer;
    delete musicplayer;
    delete musicPlaylist;
    delete startingDialog;
    delete rules;
}

void MapWindow::resizeEvent(QResizeEvent *event)
{
    m_ui->gameMapView->fitInView(gameMap->sceneRect(),Qt::KeepAspectRatio);
}

void MapWindow::showEvent(QShowEvent *event)
{
    m_ui->gameMapView->fitInView(gameMap->sceneRect(),Qt::KeepAspectRatio);
}


void MapWindow::showGameMessage(std::string message)
{
    m_ui->gameDialogueBrowser->append(QString::fromStdString(message));
}

std::string MapWindow::getUsername()
{
    return username;
}

void MapWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()== Qt::Key_Plus){
        zoomIn();
    }
    else if(event->key()== Qt::Key_Minus){
        zoomOut();
    }
}

void MapWindow::on_quitButton_clicked()
{
    this->close();
}


void MapWindow::on_diceButton_clicked()
{
    soundEffectPlayer->setMedia(
                QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/dice.wav"));
    soundEffectPlayer->play();
    showGameMessage("You threw a " + std::to_string(eventHandler->throwDice()));
    m_ui->diceButton->setDisabled(true);
    m_ui->endTurnButton->setDisabled(false);
}

void MapWindow::on_endTurnButton_clicked()
{
    eventHandler->endTurn();

    m_ui->diceButton->setDisabled(false);
    m_ui->endTurnButton->setDisabled(false);
    m_ui->searchAreaButton->setDisabled(false);
    m_ui->moveButton->setDisabled(false);
    m_ui->buildButton->setDisabled(false);
    m_ui->hireButton->setDisabled(false);

    m_ui->buildButton->setChecked(false);
    m_ui->hireButton->setChecked(false);
    m_ui->moveButton->setChecked(false);
    m_ui->searchAreaButton->setChecked(false);

    eventHandler->setPlayerMoved(false);
    eventHandler->setPlayerSearched(false);
    eventHandler->setPlayerHired(false);
    eventHandler->setPlayerBuilt(false);

    eventHandler->setMoving(false);
    eventHandler->setBuildingState(false);
    eventHandler->setHiring(false);
    eventHandler->setSearching(false);
    buttons_update();

    showGameMessage("");
    showGameMessage("Turn number: "+std::to_string(eventHandler->getTurn()));
}

void MapWindow::setUsername(std::string name)
{
    username = name;
}


void MapWindow::on_moveButton_toggled(bool checked)
{
    if(checked==true && eventHandler->getPlayerMoved() == false){
        if(eventHandler->getThrown() == true){
            eventHandler->setMoving(true);
            lock_and_unlock_other_buttons(true);
            showGameMessage("Moving. Select a tile to move to.");

        }
        else{
            showGameMessage("You haven't thrown the dice yet."
                            " Throw the dice to be able to move.");

            m_ui->moveButton->setChecked(false);
            lock_and_unlock_other_buttons(false);
            buttons_update();
        }
    }
    else if (checked == false && eventHandler->isMoving() == true){
        eventHandler->setMoving(false);
        lock_and_unlock_other_buttons(false);
        showGameMessage("Stopped moving. Select an action.");
        buttons_update();

    }

}

void MapWindow::zoomIn()
{
    m_ui->gameMapView->scale(1.1,1.1);
}

void MapWindow::zoomOut()
{
    m_ui->gameMapView->scale(0.9,0.9);
}

void MapWindow::on_buildButton_toggled(bool checked)
{
    if(checked==true && eventHandler->getPlayerBuilt() == false){
        eventHandler->setBuildingState(true);
        lock_and_unlock_other_buttons(true);

        showGameMessage("Bulding. First select a building"
                        " and then click a tile to build to.");
    }
    else if(checked == false && eventHandler->isBuilding() == true){
        eventHandler->setBuildingState(false);
        lock_and_unlock_other_buttons(false);
        showGameMessage("Stopped building. Select an action.");
        buttons_update();
    }



}

void MapWindow::on_searchAreaButton_toggled(bool checked)
{
    if(checked==true && eventHandler->getPlayerSearched() == false){
        soundEffectPlayer->setMedia(
                    QUrl::fromLocalFile(
                        "../../juho-ja-leo/Game/Music/hmm.wav"));

        soundEffectPlayer->play();
        eventHandler->setSearching(true);
        lock_and_unlock_other_buttons(true);
        showGameMessage("Searching. First select a tile next to you "
                        "and then click a tile to search it.");
    }
    else if(checked == false && eventHandler->isSearching() == true){
        eventHandler->setSearching(false);
        lock_and_unlock_other_buttons(false);
        showGameMessage("Stopped searching. Select an action.");
        buttons_update();
    }
}

void MapWindow::treasureFoundSound()
{
    soundEffectPlayer->setMedia(
                QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/woohoo.wav"));
    soundEffectPlayer->play();
}

void MapWindow::robberFoundSound()
{
    soundEffectPlayer->setMedia(
                QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/scream.wav"));
    soundEffectPlayer->play();
}

void MapWindow::nothingFoundSound()
{
    soundEffectPlayer->setMedia(
                QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/rustle.wav"));
    soundEffectPlayer->play();
}

void MapWindow::buildSound()
{
    soundEffectPlayer->setMedia(
                QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/building.wav"));
    soundEffectPlayer->play();
}

void MapWindow::on_hireButton_toggled(bool checked)
{
    if(checked == true && eventHandler->getHired() == false){
        eventHandler->setHiring(true);
        lock_and_unlock_other_buttons(true);
        showGameMessage("Hiring. "
                        "Select a tile where you want to hire a worker.");
    }
    else if(checked == false && eventHandler->isHiring() ==true){
        eventHandler->setHiring(false);
        lock_and_unlock_other_buttons(false);
        showGameMessage("Stopped hiring. Select an action.");
        buttons_update();
    }
}

void MapWindow::on_hiringList_currentIndexChanged(const QString &arg1)
{
    if (arg1.toStdString() == "Novice worker"){
        eventHandler->setWorkerType("novice worker");
    }
    else if(arg1.toStdString() == "Apprentice worker"){
        eventHandler->setWorkerType("apprentice worker");
    }
    else if(arg1.toStdString() == "Master worker"){
        eventHandler->setWorkerType("master worker");
    }

}

void MapWindow::buttons_update()
{
    if(eventHandler->getPlayerMoved()){
        m_ui->moveButton->setDisabled(true);
    }
    else{
        m_ui->moveButton->setDisabled(false);
    }
    if(eventHandler->getPlayerBuilt()){
        m_ui->buildButton->setDisabled(true);
    }
    else{
        m_ui->buildButton->setDisabled(false);
    }
    if(eventHandler->getPlayerSearched()){
        m_ui->searchAreaButton->setDisabled(true);
    }
    else{
        m_ui->searchAreaButton->setDisabled(false);
    }
    if(eventHandler->getHired()){
        m_ui->hireButton->setDisabled(true);
    }
    else{
        m_ui->hireButton->setDisabled(false);
    }
}

void MapWindow::lock_and_unlock_other_buttons(bool toggle)
{
    if(toggle == true){
        m_ui->endTurnButton->setDisabled(true);
        if(eventHandler->isMoving() == false){
            m_ui->moveButton->setDisabled(true);
        }
        else{
            m_ui->moveButton->setDisabled(false);
        }
        if(eventHandler->isBuilding() == false){
            m_ui->buildButton->setDisabled(true);
        }
        else{
            m_ui->buildButton->setDisabled(false);
        }
        if(eventHandler->isSearching() == false){
            m_ui->searchAreaButton->setDisabled(true);
        }
        else{
            m_ui->searchAreaButton->setDisabled(false);
        }
        if(eventHandler->isHiring() == false){
            m_ui->hireButton->setDisabled(true);
        }
        else{
            m_ui->hireButton->setDisabled(false);
        }
    }
    else{
        m_ui->endTurnButton->setDisabled(false);
        m_ui->moveButton->setDisabled(false);
        m_ui->moveButton->setChecked(false);

        m_ui->buildButton->setDisabled(false);
        m_ui->buildButton->setChecked(false);

        m_ui->searchAreaButton->setDisabled(false);
        m_ui->searchAreaButton->setChecked(false);

        m_ui->hireButton->setDisabled(false);
        m_ui->hireButton->setChecked(false);

    }
}

void MapWindow::on_rulesButton_clicked()
{
    rules->show();
}

void MapWindow::gameOver(gameOverState state)
{
    QMessageBox *gameOverBox = new QMessageBox(this);
    int money = objManager->getPlayer()->getResources().at(Course::MONEY);
    if(state == BANKRUPT){
        gameOverBox->setWindowTitle("You suck!");
        gameOverBox->setText("You ran out money. "
                             "Adam Smith would be ashamed of you!\n\n"
                             "Better luck next time.");
    }
    else if(state == NO_PROFIT){
        int startingMoney = Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES.at(Course::MONEY);
        if(money <= startingMoney){
            gameOverBox->setWindowTitle("Do better!");
            gameOverBox->setText("Although you did't go bankrupt,"
                                 " you did't earn any money either. "
                                 "That is not how capitalism should work!\n\n"
                                 "Try again if you dare.");
        }
    }
    else if(state == GOT_RICH){
        gameOverBox->setWindowTitle("Nice!");
        gameOverBox->setText("Great job, " + QString::fromStdString(username) +
                             "! You made " + QString::fromStdString(
                                 std::to_string(money)) +
                             " and you're now richer than ever while "
                             "finns are even poorer!\n\n"
                             "Try again to do even better.");
    }
    else if(state == LATE){
        gameOverBox->setWindowTitle("Too Late!");
        gameOverBox->setText("You didn't make it back to town in time"
                             " and now you are stuck with these weird finns. "
                             "Life sucks now that you won't be able "
                             "to get home to your favourite tea, biscuits and"
                             "writing literature. "
                             "You lost the game.");
    }
    else if(state == NO_TREASURE){
        gameOverBox->setWindowTitle("No Treasure!");
        gameOverBox->setText("You didn't find any treasures. This was supposed"
                             " to be an adventure! Adam Smith got bored to"
                             " death. \n\n You lost the game.");
    }
    gameOverBox->setStandardButtons(QMessageBox::Close);
    gameOverBox->exec();
    delete gameOverBox;
    this->close();
}

void MapWindow::updateMoneyLabel(int amount)
{
    m_ui->moneyAmountLabel->setText(
                QString::fromStdString(std::to_string(amount)));
}
}

void Game::MapWindow::on_pricesButton_clicked()
{
    prices->show();
}
