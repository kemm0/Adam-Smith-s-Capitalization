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

namespace Game{

class GameMapGenerator{
public:
    GameMapGenerator(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler);
    ~GameMapGenerator();
    void createMapObjects(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler);
    void createBuilding(Course::Coordinate location);
    Course::Coordinate getRandomMapCoordinate();
    void setTreasure();
    void setRobber();

private:
    std::vector<std::vector<int>> mapTemplate;
    std::shared_ptr<GameObjectManager> objManager_;
    std::shared_ptr<GameEventHandler> eventHandler_;
    int mapWidth;
    int mapHeight;
};
}

#endif // GAMEMAPGENERATOR_H
