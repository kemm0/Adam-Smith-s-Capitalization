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

}

Map::~Map()
{
    delete player;
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto item : items()){
        if(item->graphicsEffect() != nullptr){
            delete item->graphicsEffect();
            item->setGraphicsEffect(nullptr);
        }
    }
    QGraphicsItem* targetTile = itemAt(event->scenePos(),QTransform());
    if(eventHandler_->isMoving()== true
            && eventHandler_->getPlayerMoved() == false){
        showRangeEffect(targetTile, "move");
    }
    else if(eventHandler_->isBuilding()== true
            && eventHandler_->getPlayerBuilt() == false){
        showRangeEffect(targetTile, "build");
    }
    else if(eventHandler_->isSearching()== true
            && eventHandler_->getPlayerSearched() == false){
        showRangeEffect(targetTile, "search");
    }
    else if(eventHandler_->isHiring()== true
            && eventHandler_->getHired() == false){
        showRangeEffect(targetTile, "hire");
    }
    else{
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
    playerImg->setZValue(1000); //always draws player on top
    player = playerImg;
    addItem(playerImg);
}

void Map::move(std::shared_ptr<GameTileBase> gameTile)
{
    if(onRange == true){
        int x = gameTile->getCoordinate().x();
        int y = gameTile->getCoordinate().y();
        objManager_->getPlayer()->setCoordinate(Course::Coordinate(x,y));
        player->setPos(x,y);
        eventHandler_->setPlayerMoved(true);
        update();
    }
}

void Map::hire(std::shared_ptr<GameTileBase> gameTile)
{
    auto buildings = objManager_->getPlayer()->getObjects();
    try {
        mapGenerator_->createWorker(gameTile);
        eventHandler_->setPlayerHired(true);
    } catch (Course::IllegalAction) {
    }
}

void Map::build(std::shared_ptr<GameTileBase> gameTile)
{
    int x = gameTile->getCoordinate().x();
    int y = gameTile->getCoordinate().y();
    try {
        mapGenerator_->createBuilding(Course::Coordinate(x,y));
        QGraphicsPixmapItem* mapItem = new QGraphicsPixmapItem(
                    gameTile->getSprite());

        mapItem->setPos(x,y);
        addItem(mapItem);
        eventHandler_->setPlayerBuilt(true);
        emit built();
        update();
    } catch (Course::IllegalAction) {
    }

}

void Map::search(std::shared_ptr<GameTileBase> gameTile)
{
    int x = gameTile->getCoordinate().x();
    int y = gameTile->getCoordinate().y();

    if (gameTile->getRobber() == true){
        QGraphicsPixmapItem* robberSprite = new QGraphicsPixmapItem(
                    QPixmap("../../juho-ja-leo/Game/Sprites/robbersmall.png"));
        robberSprite->setPos(x,y);
        addItem(robberSprite);
        eventHandler_->modifyResources(
                    objManager_->getPlayer(),
                    Game::ConstGameResourceMap::ROBBER);
        emit robberFound();
    }
    else if(gameTile->getTreasure() == true){
        QGraphicsPixmapItem* treasureSprite = new QGraphicsPixmapItem(
                    QPixmap("../../juho-ja-leo/Game/Sprites/treasure.png"));
        treasureSprite->setPos(x,y);
        addItem(treasureSprite);
        eventHandler_->modifyResources(objManager_->getPlayer(),
                                       Game::ConstGameResourceMap::TREASURE);
        emit treasureFound();
    }
    else{
        QGraphicsPixmapItem* crossSprite = new QGraphicsPixmapItem(
                    QPixmap("../../juho-ja-leo/Game/Sprites/cross.png"));
        crossSprite->setPos(x,y);
        addItem(crossSprite);
        emit nothingFound();

    }
    eventHandler_->modifyResources(objManager_->getPlayer(),
                                   ConstGameResourceMap::SEARCH);
    eventHandler_->setPlayerSearched(true);
    update();
}

void Map::inspect(std::shared_ptr<GameTileBase> gameTile)
{
    if(gameTile->getType() == "Town"){
        emit inspectTile(gameTile->getDescription("brief") + "\n\n");
    }
    else {
        try {
            emit inspectTile(gameTile->getDescription("brief") +
                                ".\nThere are " + std::to_string(
                                    gameTile->getBuildingCount())
                                + " buildings and " + std::to_string(
                                    gameTile->getWorkerCount()) +
                                " workers in this area.\n\n");

        } catch (Course::KeyError()) {
            emit inspectTile("I dont know anything about this area.");
        }
    }

}





void Map::showRangeEffect(QGraphicsItem* targetTile, std::string action)
{
    if(targetTile != nullptr){

        QGraphicsColorizeEffect* graphicsEffect = new QGraphicsColorizeEffect;
        int x_distance = int(objManager_->getPlayer()->getCoordinate().x()
                            - targetTile->pos().x());
        int y_distance = int(objManager_->getPlayer()->getCoordinate().y()
                            - targetTile->pos().y());
        int validDistance = 0;
        bool sameTile = (x_distance == 0 && y_distance == 0);
        bool notValidTile = true;

        if(action == "move"){
            validDistance = eventHandler_->getDiceValue() * TILE_WIDTH;
            notValidTile = (    x_distance > validDistance
                            || x_distance < -validDistance
                            || y_distance > validDistance
                            || y_distance < -validDistance);
        }
        else if (action == "build" || action == "search"){
            validDistance = TILE_WIDTH;
            notValidTile = (x_distance > validDistance
                    || x_distance < -validDistance
                    || y_distance > validDistance
                    || y_distance < -validDistance);
        }
        else if(action == "hire"){
            auto gameTile = objManager_->getTile(
                        Course::Coordinate(
                        int(targetTile->pos().x()),
                        int(targetTile->pos().y())));
            notValidTile = (gameTile->getBuildingCount() == 0);
        }

        if(sameTile){
            graphicsEffect->setColor(QColor(Qt::red));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        else if(notValidTile){
            graphicsEffect->setColor(QColor(Qt::red));
            graphicsEffect->setStrength(0.3);
            onRange = false;
        }
        else{
            graphicsEffect->setColor(QColor(Qt::green));
            graphicsEffect->setStrength(0.3);
            onRange = true;
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
            inspect(gameTile);
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
                move(gameTile);
            }

            else if(buildSelected){
                build(gameTile);
            }
            else if(searchSelected){
                search(gameTile);
            }
            else if(hireSelected){
                hire(gameTile);

            }
        }
    }
}
}
