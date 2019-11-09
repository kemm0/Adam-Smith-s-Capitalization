#include "map.h"

Map::Map(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    sprites = {};
    tileSize = 50;
    mapWidth = 20;
    mapHeight = 20;
    setSceneRect(0,0,tileSize*mapWidth-4,tileSize*mapHeight-4);
    vMap = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0},
        {3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,0,0,0,0,0},
        {3,3,3,3,3,3,3,0,0,0,0,3,3,3,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0},
        {1,1,1,1,3,3,3,1,1,1,1,1,1,1,3,3,3,3,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,3,3,3},
        {3,3,0,3,3,3,3,3,0,0,3,3,3,0,0,0,0,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3},


    };
    drawMap();

}

void Map::drawMap()
{
    QPen pen;
    for(unsigned int i = 0; i < vMap.size(); i++){
        for(unsigned int j = 0; j < vMap.at(i).size();j++){
            int tileCode = vMap.at(j).at(i);
            QGraphicsPixmapItem* tile;
            if(tileCode == 0){
                tile = addPixmap(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/grasstile2.png"));
            }
            else if(tileCode == 1){
                tile = addPixmap(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/water.png"));
            }

            else if(tileCode == 3){
                tile = addPixmap(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/forest.png"));
            }
            tile->setPos(i*tileSize,j*tileSize);
            sprites.push_back(tile);
        }
    }
    QGraphicsPixmapItem* adamSmith = addPixmap(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/adamsmith.png"));
    adamSmith->setPos(50,50);
    adamSmith->setScale(0.1);
    player = adamSmith;
    sprites.push_back(adamSmith);
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        std::cout<<mouseEvent->scenePos().x()<<std::endl;
        std::cout<<mouseEvent->scenePos().y()<<std::endl;
        player->setPos(mouseEvent->scenePos().x()-tileSize/2,mouseEvent->scenePos().y()-tileSize/2);
        update();
    }
}
