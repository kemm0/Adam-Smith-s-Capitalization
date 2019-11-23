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
    //setBackgroundBrush(Qt::black);

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
        if(item->graphicsEffect() != nullptr){
            delete item->graphicsEffect();
            item->setGraphicsEffect(0);
        }
    }
    if(eventHandler_->isMoving()== true && eventHandler_->getPlayerMoved() == false){
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileMovableEffect(targetTile);
    }
    else{
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileHighlightEffect(targetTile);
    }
    update();
}

void Map::drawMap()
{
    for(unsigned int i = 0; i < objManager_->getGameObjects().size();i++){
        auto x = objManager_->getGameObjects().at(i);
        if(objManager_->getGameObjects().at(i)->getType()=="Grassland"){
            QGraphicsPixmapItem* tmp = new QGraphicsPixmapItem(sprites.at("Grassland"));
            tmp->setPos(x->getCoordinate().x(),x->getCoordinate().y());
            addItem(tmp);
        }
    }
    addItem(objManager_->getPlayer()->sprite);
}

void Map::showTileMovableEffect(QGraphicsItem* targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* x = new QGraphicsColorizeEffect;
        qreal x_distance = objManager_->getPlayer()->sprite->pos().x() - targetTile->pos().x();
        qreal y_distance = objManager_->getPlayer()->sprite->pos().y() - targetTile->pos().y();
        int scenedistance = eventHandler_->getDiceValue() * 50;
        if(x_distance > scenedistance|| x_distance < -scenedistance|| y_distance > scenedistance || y_distance < -scenedistance){  //check if player is too far away
            x->setColor(QColor(Qt::red)); //if too far away, show red tile
            x->setStrength(0.3);
        }
        else{
            x->setColor(QColor(Qt::green));  //if not, show green tile
            x->setStrength(0.3);
        }
        targetTile->setGraphicsEffect(x);
    }

}

void Map::showTileHighlightEffect(QGraphicsItem* targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* x = new QGraphicsColorizeEffect;
        x->setColor(QColor(Qt::white));
        x->setStrength(0.1);
        targetTile->setGraphicsEffect(x);
    }
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(eventHandler_->getThrown() && eventHandler_->getPlayerMoved() == false && eventHandler_->isMoving() == true){
        if(mouseEvent->button() == Qt::LeftButton){
            auto targetTile = itemAt(mouseEvent->scenePos(),QTransform());
            if(targetTile != nullptr){
                objManager_->getPlayer()->sprite->setPos(targetTile->pos().x(),targetTile->pos().y());
            }
            eventHandler_->setPlayerMoved(true);
            update();
        }
    }
}

void Map::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if(wheelEvent->delta() > 0){
        emit scrollIn();
    }
    else if (wheelEvent->delta()){
        emit scrollOut();
    }
}
}

