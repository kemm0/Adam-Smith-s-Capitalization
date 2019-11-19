#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <iostream>


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
    showGameMessage("Welcome " + username + "!");
    m_ui->endTurnButton->setDisabled(true);
    //std::cout<<objManager->size<<std::endl;
    //std::cout<<mapCreator->mapTemplate.size()<<std::endl;
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


void MapWindow::on_quitButton_clicked()
{
    this->close();
}

void MapWindow::on_pushButton_2_clicked()
{
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
