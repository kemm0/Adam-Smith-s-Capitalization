#include "map.h"
namespace Game{

Map::Map(QObject *parent,
         std::shared_ptr<GameObjectManager> objectsManager,
         std::shared_ptr<GameEventHandler> eventsHandler)
    : QGraphicsScene(parent),
      objectManager_(objectsManager),
      eventHandler_(eventsHandler)
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
                GrassTile* x = new GrassTile(Course::Coordinate(j,i),eventHandler_,objectManager_);
                x->sprite->setPos(i*tileSize,j*tileSize);
                addItem(x->sprite);
            }
        }
    }
    player_ = std::make_shared<Player>("Adam Smith");
    player_->sprite->setPos(50,50);
    player_->sprite->setScale(0.1);
    addItem(player_->sprite);
    //std::cout<<player_->getName()<<std::endl;

}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        player_->sprite->setPos(mouseEvent->scenePos().x()-tileSize/2,mouseEvent->scenePos().y()-tileSize/2);
        update();
    }
}
}
