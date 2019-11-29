#include "map.h"

namespace Game{
Map::Map(QObject *parent,std::shared_ptr<Game::GameEventHandler> eventHandler,std::shared_ptr<Game::GameObjectManager> objManager, std::shared_ptr<Game::GameMapGenerator> mapGenerator)
    : QGraphicsScene(parent)
{
    tileSize = 50;
    mapWidth = 20;
    mapHeight = 20;
    setSceneRect(0,0,tileSize*mapWidth-4,tileSize*mapHeight-4);
    eventHandler_ = eventHandler;
    objManager_ = objManager;
    mapGenerator_ = mapGenerator;
    player = nullptr;
    //setBackgroundBrush(Qt::black);

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
    else if(eventHandler_->isBuilding()== true && eventHandler_->getPlayerBuilt() == false){
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileBuildOrSearchEffect(targetTile);
    }
    else if(eventHandler_->isSearching()== true && eventHandler_->getPlayerSearched() == false){
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileBuildOrSearchEffect(targetTile);
    }
    else{
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileHighlightEffect(targetTile);
    }
    update();
}

void Map::drawMap()
{
    for(unsigned int i = 0; i < objManager_->getGameTiles().size();i++){
        auto x = objManager_->getGameTiles().at(i);
        QGraphicsPixmapItem* mapItem = new QGraphicsPixmapItem(x->getSprite());
        mapItem->setPos(x->getCoordinate().x(),x->getCoordinate().y());
        addItem(mapItem);
    }
    QGraphicsPixmapItem* playerImg = new QGraphicsPixmapItem(objManager_->getPlayer()->getSprite());
    playerImg->setPos(objManager_->getPlayer()->getCoordinate().x(),objManager_->getPlayer()->getCoordinate().y());
    playerImg->setZValue(1000);
    player = playerImg;
    addItem(playerImg);
}





void Map::showTileMovableEffect(QGraphicsItem* targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* x = new QGraphicsColorizeEffect;
        qreal x_distance = objManager_->getPlayer()->getCoordinate().x() - targetTile->pos().x();
        qreal y_distance = objManager_->getPlayer()->getCoordinate().y() - targetTile->pos().y();
        int scenedistance = eventHandler_->getDiceValue() * 50;
        if(x_distance == 0 && y_distance == 0){
            x->setColor(QColor(Qt::red)); //if too far away, show red tile
            x->setStrength(0.3);
            setOnRange(false);
        }
        else if(x_distance > scenedistance|| x_distance < -scenedistance|| y_distance > scenedistance || y_distance < -scenedistance){  //check if player is too far away
            x->setColor(QColor(Qt::red)); //if too far away, show red tile
            x->setStrength(0.3);
            setOnRange(false);
        }
        else{
            x->setColor(QColor(Qt::green));  //if not, show green tile
            x->setStrength(0.3);
            setOnRange(true);
        }
        targetTile->setGraphicsEffect(x);
    }

}

void Map::showTileBuildOrSearchEffect(QGraphicsItem *targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* x = new QGraphicsColorizeEffect;
        qreal x_distance = objManager_->getPlayer()->getCoordinate().x() - targetTile->pos().x();
        qreal y_distance = objManager_->getPlayer()->getCoordinate().y() - targetTile->pos().y();
        int scenedistance = 1 * 50;
        if(x_distance == 0 && y_distance == 0){
            x->setColor(QColor(Qt::white));
            x->setStrength(0.3);
            setOnRange(false);
        }
        else if(x_distance > scenedistance|| x_distance < -scenedistance|| y_distance > scenedistance || y_distance < -scenedistance){  //check if player is too far away
            x->setColor(QColor(Qt::white)); //if too far away, show white tile
            x->setStrength(0.3);
            setOnRange(false);
        }
        else{
            x->setColor(QColor(Qt::yellow));  //if not, show yellow tile
            x->setStrength(0.3);
            setOnRange(true);
        }
        targetTile->setGraphicsEffect(x);
    }
}

void Map::setOnRange(bool on_range)
{
    range = on_range;
}

bool Map::getOnRange()
{
    return range;
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
    auto targetTile = itemAt(mouseEvent->scenePos(),QTransform());
    if(eventHandler_->getThrown() && eventHandler_->getPlayerMoved() == false && eventHandler_->isMoving() == true){
        if(mouseEvent->button() == Qt::LeftButton){
            if(targetTile != nullptr && getOnRange() == true && objManager_){
                objManager_->getPlayer()->setCoordinate(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
                player->setPos(targetTile->pos());
                eventHandler_->setPlayerMoved(true);
                update();
            }
        }
    }

    else if(eventHandler_->isBuilding()){
        if(mouseEvent->button() == Qt::LeftButton){
            if(targetTile != nullptr && eventHandler_->getPlayerBuilt() == false && eventHandler_->isBuilding() == true
                    && getOnRange() == true){
                mapGenerator_->createBuilding(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
                //std::cout<<objManager_->getGameTile(Course::Coordinate(targetTile->pos().x(),targetTile->pos().y()))->getType()<<std::endl;
                auto x = objManager_->getGameTile(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
                QGraphicsPixmapItem* mapItem = new QGraphicsPixmapItem(x->getSprite());
                mapItem->setPos(targetTile->pos());
                addItem(mapItem);
                //removeItem(targetTile);
                eventHandler_->setPlayerBuilt(true);
                emit built();
                update();
            }
        }
    }
    else if(eventHandler_->isSearching()){
        if(mouseEvent->button() == Qt::LeftButton){
            if(targetTile != nullptr && eventHandler_->getPlayerSearched() == false && eventHandler_->isSearching() == true
                    && getOnRange() == true){
                auto x = objManager_->getGameTile(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
                if (x->getRobber() == true){
                    QGraphicsPixmapItem* robberSprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/robbersmall.png"));
                    robberSprite->setPos(targetTile->pos());
                    addItem(robberSprite);
                    objManager_->getPlayer()->setMoney(Game::ConstGameResourceMap::ROBBER);
                    emit robberFound();

                }
                else if(x->getTreasure() == true){
                    QGraphicsPixmapItem* treasureSprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/treasure.png"));
                    treasureSprite->setPos(targetTile->pos());
                    addItem(treasureSprite);
                    objManager_->getPlayer()->setMoney(Game::ConstGameResourceMap::TREASURE);
                    emit treasureFound();
                }
                else{
                    QGraphicsPixmapItem* crossSprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/cross.png"));
                    crossSprite->setPos(targetTile->pos());
                    addItem(crossSprite);
                    emit nothingFound();

                }
                eventHandler_->setPlayerSearched(true);
                update();
            }
        }
    }
    else if(targetTile != nullptr && eventHandler_->isHiring()){
        if(mouseEvent->button() == Qt::LeftButton){
            auto buildings = objManager_->getPlayer()->getObjects();
            auto x = objManager_->getGameTile(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
            mapGenerator_->createWorker(x);
        }

    }
    else{
        //std::cout<<"Graphicsitem location x: " + std::to_string(int(targetTile->pos().x()))+ " y: " + std::to_string(int(targetTile->pos().y()))<<std::endl;
        auto tile = objManager_->getGameTile(Course::Coordinate(int(targetTile->pos().x()),int(targetTile->pos().y())));
        emit inspectTile("This is " + tile->getType() + ". There are " + std::to_string(tile->getBuildingCount()) + " buildings and " + std::to_string(tile->getWorkerCount()) + " workers in this area.");
        //std::cout<<"Database tile x: " + std::to_string(y->getCoordinate().x()) + " y: " + std::to_string(y->getCoordinate().y())<<std::endl;
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
