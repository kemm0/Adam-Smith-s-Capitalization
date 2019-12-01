#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <iostream>
#include "QMediaPlaylist"

namespace Game{
MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow)
{
    startingDialog = new startDialog();
    connect(startingDialog,&startDialog::nameConfirmed,this,&MapWindow::setUsername);
    startingDialog->exec();
    m_ui->setupUi(this);
    setWindowIcon(QIcon(QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png")));
    setWindowTitle("Adam Smith's Capitalization");
    //this->setWindowState(Qt::WindowFullScreen);   //Sets fullsceen mode
    objManager = std::make_shared<Game::GameObjectManager>();
    eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    mapCreator = std::make_shared<Game::GameMapGenerator>(objManager,eventHandler);

    //objManager->initMap(eventHandler);
    gameMap = new Game::Map(nullptr,eventHandler,objManager,mapCreator);
    gameMap->drawMap();
    m_ui->gameMapView->setScene(gameMap);
    m_ui->gameMapView->setMouseTracking(true);
    m_ui->gameMapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    showGameMessage("Hello " + username + "! \n"
                                          "Get ready to conquer Pirkanmaa"
                    );
    m_ui->endTurnButton->setDisabled(false);
    m_ui->moveButton->setCheckable(true);
    m_ui->buildButton->setCheckable(true);
    m_ui->searchAreaButton->setCheckable(true);
    m_ui->hireButton->setCheckable(true);


    showGameMessage("Money: " + std::to_string(objManager->getPlayer()->getMoney()));

    //MUSIC
    musicplayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist();
    musicPlaylist->addMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/gamemusic.wav"));
    musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    musicplayer->setPlaylist(musicPlaylist);
    musicplayer->play();

    //SOUND EFFECTS
    soundEffectPlayer = new QMediaPlayer();
    connect(gameMap,&Map::robberFound,this,&MapWindow::robberFoundSound);
    connect(gameMap,&Map::treasureFound,this,&MapWindow::treasureFoundSound);
    connect(gameMap,&Map::nothingFound,this,&MapWindow::nothingFoundSound);
    connect(gameMap,&Map::built,this,&MapWindow::buildSound);

    connect(gameMap,&Map::inspectTile,this,&MapWindow::showTileInfo);
    connect(mapCreator.get(),&GameMapGenerator::gameMessage,this,&MapWindow::showGameMessage);
    connect(eventHandler.get(), &GameEventHandler::gameOver, this, &MapWindow::gameOver);

    gameMap->setBackgroundBrush(Qt::black);
    m_ui->gameMapView->scale(0.9,0.9);
    maxTurns = 20;
}

MapWindow::~MapWindow()
{
    delete m_ui;
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
    soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/dice.wav"));
    soundEffectPlayer->play();
    showGameMessage("You threw a " + std::to_string(eventHandler->throwDice()));
    m_ui->diceButton->setDisabled(true);
    m_ui->endTurnButton->setDisabled(false);
}

void MapWindow::on_endTurnButton_clicked()
{
    if(maxTurns - eventHandler->getTurn() == 0){
        gameOver(false);
    }
    eventHandler->endTurn();
    showGameMessage("Turns left: "+std::to_string(maxTurns - eventHandler->getTurn()));
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

    showGameMessage("Money: " + std::to_string(objManager->getPlayer()->getMoney()));
    showGameMessage("");
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
            showGameMessage("You haven't thrown the dice yet. Throw the dice to be able to move.");
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
        eventHandler->setSelectedBuildingType(m_ui->buildingsList->currentText().toStdString());
        showGameMessage("Bulding a " + eventHandler->getSelectedBuildingType()+  ". First select a building and then click a tile to build to.");
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
        soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/hmm.wav"));
        soundEffectPlayer->play();
        eventHandler->setSearching(true);
        lock_and_unlock_other_buttons(true);
        showGameMessage("Searching. First select a tile next to you and then click a tile to search it.");
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
    soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/woohoo.wav"));
    soundEffectPlayer->play();
}

void MapWindow::robberFoundSound()
{
    soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/scream.wav"));
    soundEffectPlayer->play();
}

void MapWindow::nothingFoundSound()
{
    soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/rustle.wav"));
    soundEffectPlayer->play();
}

void MapWindow::buildSound()
{
    soundEffectPlayer->setMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/building.wav"));
    soundEffectPlayer->play();
}

void MapWindow::showTileInfo(std::string info)
{
    showGameMessage(info);
}



void MapWindow::on_hireButton_toggled(bool checked)
{
    if(checked == true && eventHandler->getHired() == false){
        eventHandler->setHiring(true);
        lock_and_unlock_other_buttons(true);
        showGameMessage("Hiring. Select a tile where you want to hire a worker.");
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
    if (arg1.toStdString() == "Novice worker (30)"){
        eventHandler->setWorkerType("novice worker");
    }
    else if(arg1.toStdString() == "Apprentice worker (50)"){
        eventHandler->setWorkerType("apprentice worker");
    }
    else if(arg1.toStdString() == "Master worker (70)"){
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
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Game rules");
    msgBox->setText("How to play:");
    msgBox->setInformativeText("In this game you play as Adam Smith, father of capitalism! Your aim is to earn money by building houses, "
                               "hiring dirty finns to work for you and searching for treasures while avoiding robbers and alcoholics.\n\n"
                               "One turn composes of four possible actions that can be made in arbitrary order: Moving, seaching, building and hiring. "
                               "Most actions are done by clicking a button and then clicking a tile in the map.\n\n"
                               "Moving: You can move to any direction an amount specified by dice. Make sure to throw the dice before moving.\n\n"
                               "Searching: You can search a tile next to you. There is a chance of finding a great treasure as well as being robbed.\n\n"
                               "Building: Build a house in an row in tile away from you. Different buildings cost different amounts "
                               "and produce different amounts of money. To cance building just press the build-button again\n\n"
                               "Hiring: You can hire people working in any of your buildings. Hiring a skilled person costs more but also"
                               "yields a greater bonus to buildings production.\n\n"
                               "Young money, cash money!");
    msgBox->setDetailedText("Backstory\n\n"
                            "Unknown to most, Adam Smith, the forefather of capitalism and an absolute mad lad, "
                            "made a secret detour on his way from Glasgow to Toulouse. "
                            "What could be the reason for this detour? Where did Smith go? What did he find?!\n\n"
                            "As a young lad living in 1700s Scotland, Smith had a severe accident. "
                            "This near-death experience led Smith to question his entire life. "
                            "After years spent in solitude meditating, Smith finally figured it out: It's all about money!\n\n"
                            "Inspired by his revolutionary idea, Smith devoted his life for spreading the joyful word of capitalism. "
                            "Unfortunately, not everyone agreed with Smith. A small county in a cold, dark and uncivilized "
                            "country far up north had declared its disinterest on capitalistic worldview. The name of this small county was Pirkanmaa?"
                            "Play as Adam Smith the father of capitalism in 1700s Pirkanmaa.\n\n"
                            "Show the dirty finns how capitalism solves all the problems by robbing their natural "
                            "resources and forcing them to work in sweatshops. Experience the glory and satisfaction "
                            "in making as much money as possible as well as claim your part of the happiness that capitalism has "
                            "brought us in Adam Smith's Capitalization!");
    msgBox->setStandardButtons(QMessageBox::Close);
    msgBox->exec();
    delete msgBox;
}

void MapWindow::gameOver(bool ranOutOfMoney)
{
    QMessageBox *gameOverBox = new QMessageBox(this);
    if(ranOutOfMoney == true){
        gameOverBox->setWindowTitle("You suck!");
        gameOverBox->setText("You ran out money. Adam Smith would be ashamed of you!\n\n"
                             "Better luck next time.");
    }
    else{
        int money = objManager->getPlayer()->getMoney();
        if(money <= objManager->getPlayer()->getStartingMoney()){
            gameOverBox->setWindowTitle("Do better");
            gameOverBox->setText("Although you did't go bankruptcy, you did't earn any money either. "
                                 "That is not how capitalism should work!\n\n"
                                 "Try again if you dare.");
        }
        else{
            gameOverBox->setWindowTitle("Nice!");
            gameOverBox->setText("Great job! You made " +
                                 QString::fromStdString(std::to_string(money)) +
                                 "and you're now richer than ever while finns are even poorer!\n\n"
                                 "Try again to do even better.");
        }
    }
    gameOverBox->setStandardButtons(QMessageBox::Close);
    gameOverBox->exec();
    delete gameOverBox;
    this->close();
}
}
