#ifndef GAMEMAPGENERATOR_H
#define GAMEMAPGENERATOR_H

#include "../CourseLib/core/worldgenerator.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "Tiles/grasstile.h"
#include "Tiles/foresttile.h"
#include "Tiles/towntile.h"
#include "Tiles/watertile.h"
#include "Buildings/farmbuilding.h"
#include "Buildings/loggingbuilding.h"
#include "Buildings/fishingbuilding.h"
#include "Workers/noviceworker.h"
#include "Workers/apprenticeworker.h"
#include "Workers/masterworker.h"


namespace Game{

class GameMapGenerator: public QObject{
Q_OBJECT
public:
    GameMapGenerator(std::shared_ptr<GameObjectManager> objManager,
                     std::shared_ptr<GameEventHandler> eventHandler,
                     QObject *parent = nullptr);
    ~GameMapGenerator();
    void createMapObjects();
    void createBuilding(Course::Coordinate location);
    Course::Coordinate getRandomMapCoordinate();
    void setTreasure(int amount);
    void setRobber(int amount);
    void createGrassTile(Course::Coordinate location);
    void createForestTile(Course::Coordinate location);
    void createWaterTile(Course::Coordinate location);
    void createPlayer(Course::Coordinate location);
    void createWorker(std::shared_ptr<GameTileBase> targetTile);

    void createFarmhouse(std::shared_ptr<GameTileBase> targetTile);
    void createLoggingcabin(std::shared_ptr<GameTileBase> targetTile);
    void createFishinghut(std::shared_ptr<GameTileBase> targetTile);
signals:
    void gameMessage(std::string);

private:
    std::vector<std::vector<int>> mapTemplate;
    std::shared_ptr<GameObjectManager> objManager_;
    std::shared_ptr<GameEventHandler> eventHandler_;
    int mapWidth;
    int mapHeight;

};
}

#endif // GAMEMAPGENERATOR_H
