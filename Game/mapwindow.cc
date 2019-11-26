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
    //this->setWindowState(Qt::WindowFullScreen);   //Sets fullsceen mode
    objManager = std::make_shared<Game::GameObjectManager>();
    eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    mapCreator = std::make_shared<Game::GameMapGenerator>(objManager,eventHandler);
    mapCreator->createMapObjects(objManager,eventHandler);

    //objManager->initMap(eventHandler);
    gameMap = new Game::Map(nullptr,eventHandler,objManager,mapCreator);
    gameMap->drawMap();
    m_ui->gameMapView->setScene(gameMap);
    m_ui->gameMapView->setMouseTracking(true);
    m_ui->gameMapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    showGameMessage("Hello " + username + "! \n"
                                          "Get ready to conquer Pirkanmaa"
                    );
    m_ui->endTurnButton->setDisabled(true);
    m_ui->moveButton->setCheckable(true);
    m_ui->buildButton->setCheckable(true);
    m_ui->searchAreaButton->setCheckable(true);
    showGameMessage(std::to_string(objManager->getGameTiles().size()));   

    //MUSIC
    /*musicplayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist();
    musicPlaylist->addMedia(QUrl::fromLocalFile("../../juho-ja-leo/Game/Music/gamemusic.wav"));
    musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    musicplayer->setPlaylist(musicPlaylist);
    musicplayer->play();*/

    //std::cout<<objManager->size<<std::endl;
    //std::cout<<mapCreator->mapTemplate.size()<<std::endl;
    //connect(gameMap,&Game::Map::scrollIn,this,&MapWindow::zoomIn);
    //connect(gameMap,&Game::Map::scrollOut,this,&MapWindow::zoomOut);
    //m_ui->gameMapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_ui->gameMapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameMap->setBackgroundBrush(Qt::black);
    m_ui->gameMapView->scale(0.9,0.9);
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
    //m_ui->gameMapView->ensureVisible(gameMap->sceneRect(),0,0);
    m_ui->gameMapView->fitInView(gameMap->sceneRect(),Qt::KeepAspectRatio);
    //m_ui->gameMapView->centerOn(0,0);
}

void MapWindow::initMap()
{
    /*Course::WorldGenerator* x = &Course::WorldGenerator::getInstance();
    x->addConstructor<Game::GrassTile>(10);
    x->generateMap(20,20,10,objManager,eventHandler);*/
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
    showGameMessage("You threw a " + std::to_string(eventHandler->throwDice()));
    m_ui->diceButton->setDisabled(true);
    m_ui->endTurnButton->setDisabled(false);
}

void MapWindow::on_endTurnButton_clicked()
{
    eventHandler->endTurn();
    showGameMessage("Turn number: "+std::to_string(eventHandler->getTurn()));
    m_ui->diceButton->setDisabled(false);
    m_ui->endTurnButton->setDisabled(true);
    m_ui->buildButton->setChecked(false);
    m_ui->buildButton->setDisabled(false);
    eventHandler->setPlayerBuilt(false);
    m_ui->moveButton->setChecked(false);
    m_ui->moveButton->setDisabled(false);
    eventHandler->setPlayerMoved(false);
    eventHandler->setPlayerSearched(false);
}

void MapWindow::setUsername(std::string name)
{
    username = name;
}


void MapWindow::on_moveButton_toggled(bool checked)
{
    if(checked==true){
        m_ui->buildButton->setDisabled(true);
        m_ui->searchAreaButton->setDisabled(true);
    }
    else{
        m_ui->buildButton->setDisabled(false);
        m_ui->searchAreaButton->setDisabled(false);
    }
    if(checked==true && eventHandler->getPlayerMoved() == false){
        if(eventHandler->getThrown() == true){
            eventHandler->setMoving(true);
            showGameMessage("Moving. Select a tile to move to.");


        }
        else{
            showGameMessage("You haven't thrown the dice yet. Throw the dice to be able to move.");
        }
    }
    else if (checked == false && eventHandler->isMoving() == true){
        eventHandler->setMoving(false);
        showGameMessage("Stopped moving. Select an action.");
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
}

void Game::MapWindow::on_buildButton_toggled(bool checked)
{
    if(checked==true && eventHandler->isBuilding() == false){
        m_ui->moveButton->setDisabled(true);
        m_ui->searchAreaButton->setDisabled(true);
        eventHandler->setBuildingState(true);
        eventHandler->setSelectedBuildingType(m_ui->buildingsList->currentText().toStdString());
        showGameMessage("Bulding a " + eventHandler->getSelectedBuildingType()+  ". First select a building and then click a tile to build to.");
    }
    else{
        m_ui->moveButton->setDisabled(false);
        m_ui->searchAreaButton->setDisabled(false);
        eventHandler->setBuildingState(false);
        showGameMessage("Stopped building. Select an action.");
    }



}

void Game::MapWindow::on_searchAreaButton_toggled(bool checked)
{
    if(checked==true && eventHandler->isSearching() == false){
        m_ui->moveButton->setDisabled(true);
        m_ui->buildButton->setDisabled(true);
        eventHandler->setSearching(true);
        showGameMessage("Searching. First select a tile next to you and then click a tile to search it.");
    }
    else{
        m_ui->moveButton->setDisabled(false);
        m_ui->buildButton->setDisabled(false);
        eventHandler->setSearching(false);
        showGameMessage("Stopped searching. Select an action.");
    }
}
