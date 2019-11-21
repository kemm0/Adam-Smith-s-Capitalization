#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <iostream>

namespace Game{
MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow)
{
    startingDialog = new startDialog();
    connect(startingDialog,&startDialog::nameConfirmed,this,&MapWindow::setUsername);
    startingDialog->exec();
    m_ui->setupUi(this);
    this->setWindowState(Qt::WindowFullScreen);
    objManager = std::make_shared<Game::GameObjectManager>();
    eventHandler = std::make_shared<Game::GameEventHandler>();

    mapCreator = std::make_shared<Game::GameMapGenerator>();
    mapCreator->createMapObjects(objManager,eventHandler);

    //objManager->initMap(eventHandler);
    gameMap = new Game::Map(nullptr,eventHandler,objManager);
    gameMap->drawMap();
    m_ui->gameMapView->setScene(gameMap);
    m_ui->gameMapView->setMouseTracking(true);
    m_ui->gameMapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    showGameMessage("Hello " + username + "! \n"
                                          "Get ready to conquer Pirkanmaa"
                    );
    m_ui->endTurnButton->setDisabled(true);
    m_ui->moveButton->setCheckable(true);
    //std::cout<<objManager->size<<std::endl;
    //std::cout<<mapCreator->mapTemplate.size()<<std::endl;
    //connect(gameMap,&Game::Map::scrollIn,this,&MapWindow::zoomIn);
    //connect(gameMap,&Game::Map::scrollOut,this,&MapWindow::zoomOut);
    //m_ui->gameMapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_ui->gameMapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::resizeEvent(QResizeEvent *event)
{
    m_ui->gameMapView->fitInView(gameMap->sceneRect(),Qt::IgnoreAspectRatio);
}

void MapWindow::showEvent(QShowEvent *event)
{
    m_ui->gameMapView->ensureVisible(gameMap->sceneRect(),0,0);
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
