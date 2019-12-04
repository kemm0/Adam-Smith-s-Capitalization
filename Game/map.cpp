#include "map.h"

namespace Game{
Map::Map(QObject *parent,
         std::shared_ptr<Game::GameEventHandler> eventHandler,
         std::shared_ptr<Game::GameObjectManager> objManager,
         std::shared_ptr<Game::GameMapGenerator> mapGenerator)
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
    if(eventHandler_->isMoving()== true
            && eventHandler_->getPlayerMoved() == false){
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileMovableEffect(targetTile);
    }
    else if(eventHandler_->isBuilding()== true
            && eventHandler_->getPlayerBuilt() == false){
        QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
        showTileBuildOrSearchEffect(targetTile);
    }
    else if(eventHandler_->isSearching()== true
            && eventHandler_->getPlayerSearched() == false){
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
    QGraphicsPixmapItem* playerImg = new QGraphicsPixmapItem(
                objManager_->getPlayer()->getSprite());
    int playerX = objManager_->getPlayer()->getCoordinate().x();
    int playerY = objManager_->getPlayer()->getCoordinate().y();
    playerImg->setPos(playerX,playerY);
    playerImg->setZValue(1000);
    player = playerImg;
    addItem(playerImg);
}





void Map::showTileMovableEffect(QGraphicsItem* targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* graphicsEffect = new QGraphicsColorizeEffect;
        qreal x_distance = (objManager_->getPlayer()->getCoordinate().x()
                            - targetTile->pos().x());
        qreal y_distance = (objManager_->getPlayer()->getCoordinate().y()
                            - targetTile->pos().y());

        int scenedistance = eventHandler_->getDiceValue() * 50;

        if(x_distance == 0 && y_distance == 0){
            //if too far away, show red tile
            graphicsEffect->setColor(QColor(Qt::red));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        //check if player is too far away
        else if(x_distance > scenedistance|| x_distance < -scenedistance
                || y_distance > scenedistance
                || y_distance < -scenedistance){
            //if too far away, show red tile
            graphicsEffect->setColor(QColor(Qt::red));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        else{
            //if not, show green tile
            graphicsEffect->setColor(QColor(Qt::green));
            graphicsEffect->setStrength(0.3);
            onRange = true;
        }
        targetTile->setGraphicsEffect(graphicsEffect);
    }

}

void Map::showTileBuildOrSearchEffect(QGraphicsItem *targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* graphicsEffect = new QGraphicsColorizeEffect;
        qreal x_distance = (objManager_->getPlayer()->getCoordinate().x()
                            - targetTile->pos().x());
        qreal y_distance = (objManager_->getPlayer()->getCoordinate().y()
                            - targetTile->pos().y());
        int scenedistance = 1 * 50;
        if(x_distance == 0 && y_distance == 0){
            graphicsEffect->setColor(QColor(Qt::white));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        //check if player is too far away
        else if(x_distance > scenedistance
                || x_distance < -scenedistance
                || y_distance > scenedistance
                || y_distance < -scenedistance){
             //if too far away, show white tile
            graphicsEffect->setColor(QColor(Qt::white));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        else{
            //if not, show yellow tile
            graphicsEffect->setColor(QColor(Qt::yellow));
            graphicsEffect->setStrength(0.3);
            onRange =true;
        }
        targetTile->setGraphicsEffect(graphicsEffect);
    }
}

void Map::showTileHighlightEffect(QGraphicsItem* targetTile)
{
    if(targetTile != nullptr){
        QGraphicsColorizeEffect* graphicsEffect = new QGraphicsColorizeEffect;
        graphicsEffect->setColor(QColor(Qt::white));
        graphicsEffect->setStrength(0.1);
        targetTile->setGraphicsEffect(graphicsEffect);
    }
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto targetTile = itemAt(mouseEvent->scenePos(),QTransform());
    if(targetTile != nullptr){
        auto gameTile = objManager_->getGameTile(
                    Course::Coordinate(int(targetTile->pos().x()),
                                       int(targetTile->pos().y())));
        if(mouseEvent->button() == Qt::RightButton){
            emit inspectTile(
                        "This is " + gameTile->getType() +
                        ". There are " + std::to_string(
                            gameTile->getBuildingCount())
                        + " buildings and " + std::to_string(
                            gameTile->getWorkerCount()) +
                        " workers in this area.");
        }

        else if(mouseEvent->button() == Qt::LeftButton){

            bool moveSelected = (eventHandler_->getThrown()
                                 && eventHandler_->getPlayerMoved() == false
                                 && eventHandler_->isMoving() == true);

            bool buildSelected = (eventHandler_->getPlayerBuilt() == false
                                  && eventHandler_->isBuilding() == true
                                  && onRange == true);

            bool searchSelected = (eventHandler_->getPlayerSearched() == false
                                   && eventHandler_->isSearching() == true
                                   && onRange == true);

            bool hireSelected = (eventHandler_->isHiring() == true
                                 && eventHandler_->getHired() == false);
            if(moveSelected){
                if(onRange == true){
                    objManager_->getPlayer()->setCoordinate(
                                Course::Coordinate(int(targetTile->pos().x()),
                                                   int(targetTile->pos().y())));
                    player->setPos(targetTile->pos());
                    eventHandler_->setPlayerMoved(true);
                    update();
                }
            }

            else if(buildSelected){
                mapGenerator_->createBuilding(Course::Coordinate(
                                                  int(targetTile->pos().x()),
                                                  int(targetTile->pos().y())));
                QGraphicsPixmapItem* mapItem = new QGraphicsPixmapItem(
                            gameTile->getSprite());

                mapItem->setPos(targetTile->pos());
                addItem(mapItem);
                eventHandler_->setPlayerBuilt(true);
                emit built();
                update();
            }
            else if(searchSelected){
                if (gameTile->getRobber() == true){
                    QGraphicsPixmapItem* robberSprite = new QGraphicsPixmapItem(
                                QPixmap("../../juho-ja-leo/Game/Sprites/robbersmall.png"));
                    robberSprite->setPos(targetTile->pos());
                    addItem(robberSprite);
                    eventHandler_->modifyResources(
                                objManager_->getPlayer(),
                                Game::ConstGameResourceMap::ROBBER);
                    emit robberFound();
                }
                else if(gameTile->getTreasure() == true){
                    QGraphicsPixmapItem* treasureSprite = new QGraphicsPixmapItem(
                                QPixmap("../../juho-ja-leo/Game/Sprites/treasure.png"));
                    treasureSprite->setPos(targetTile->pos());
                    addItem(treasureSprite);
                    eventHandler_->modifyResources(objManager_->getPlayer(),
                                                   Game::ConstGameResourceMap::TREASURE);
                    emit treasureFound();
                }
                else{
                    QGraphicsPixmapItem* crossSprite = new QGraphicsPixmapItem(
                                QPixmap("../../juho-ja-leo/Game/Sprites/cross.png"));
                    crossSprite->setPos(targetTile->pos());
                    addItem(crossSprite);
                    emit nothingFound();

                }
                eventHandler_->setPlayerSearched(true);
                update();
            }
            else if(hireSelected){
                    auto buildings = objManager_->getPlayer()->getObjects();
                    mapGenerator_->createWorker(gameTile);
                    eventHandler_->setPlayerHired(true);

            }
        }
    }
}
}
