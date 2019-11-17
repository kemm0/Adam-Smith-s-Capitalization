#include "map.h"

namespace Game{
Map::Map(QObject *parent,std::shared_ptr<Game::GameEventHandler> eventHandler,std::shared_ptr<Game::GameObjectManager> objManager)
    : QGraphicsScene(parent)
{
    sprites = {{"Grassland",QPixmap("../../juho-ja-leo/Game/Sprites/grasstile2.png")}};
    tileSize = 50;
    mapWidth = 20;
    mapHeight = 20;
    setSceneRect(0,0,tileSize*mapWidth-4,tileSize*mapHeight-4);
    eventHandler_ = eventHandler;
    objManager_ = objManager;

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

}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto item : items()){
        item->setGraphicsEffect(0);
    }
    QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* x = new QGraphicsColorizeEffect;
        qreal x_distance = objManager_->getPlayer()->sprite->pos().x() - targetTile->pos().x();
        std::cout<<x_distance<<std::endl;
        if(x_distance > 50 || x_distance < -50){  //check if player is too far away
            x->setColor(QColor(Qt::red)); //if too far away, show red tile
            x->setStrength(0.3);
        }
        else{
            x->setColor(QColor(Qt::green));  //if not, show green tile
            x->setStrength(0.3);
        }
        targetTile->setGraphicsEffect(x);
        //auto grid = new QGraphicsRectItem(QRectF(targetTile->pos(),QSize(50,50)));
        //addItem(new QGraphicsRectItem(QRectF(targetTile->pos(),QSize(50,50))));
    }
    update();
}

void Map::drawMap()
{
    QPen pen;
    /*for(unsigned int i = 0; i < vMap.size(); i++){
        for(unsigned int j = 0; j < vMap.at(i).size();j++){
            int tileCode = vMap.at(j).at(i);
            if(tileCode == 0){
                GrassTile* x = new GrassTile(Course::Coordinate(j,i),eventHandler,objManager);
                x->sprite->setPos(i*tileSize,j*tileSize);
                addItem(x->sprite);
            }
        }
    }*/
    for(unsigned int i = 0; i < objManager_->getGameObjects().size();i++){
        auto x = objManager_->getGameObjects().at(i);
        if(objManager_->getGameObjects().at(i)->getType()=="Grassland"){
            QGraphicsPixmapItem* tmp = new QGraphicsPixmapItem(sprites.at("Grassland"));
            tmp->setPos(x->getCoordinate().x(),x->getCoordinate().y());
            addItem(tmp);
        }
    }
    addItem(objManager_->getPlayer()->sprite);
    //std::cout<<player_->getName()<<std::endl;

}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        auto targetTile = itemAt(mouseEvent->scenePos(),QTransform());
        //player_->sprite->setPos(mouseEvent->scenePos().x()-tileSize/2,mouseEvent->scenePos().y()-tileSize/2);
        if(targetTile != nullptr){
            objManager_->getPlayer()->sprite->setPos(targetTile->pos().x(),targetTile->pos().y());

            //std::cout<<targetTile->pos().y()<<std::endl;
        }
        update();
    }
}
}

