#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <iostream>


MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow)
{
    startingDialog = new startDialog();
    startingDialog->exec();
    //tileSize = 50;
    //mapWidth = 20;
    //mapHeight = 20;
    m_ui->setupUi(this);
    this->setWindowState(Qt::WindowFullScreen);
    objManager = std::make_shared<GameObjectManager>();
    eventHandler = std::make_shared<GameEventHandler>();
    gameMap = new Map(nullptr,objManager,eventHandler);
    m_ui->gameMapView->setScene(gameMap);
    m_ui->gameMapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
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


void MapWindow::on_quitButton_clicked()
{
    this->close();
}

void MapWindow::on_pushButton_2_clicked()
{
}
