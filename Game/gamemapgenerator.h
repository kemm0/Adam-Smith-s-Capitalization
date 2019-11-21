#ifndef GAMEMAPGENERATOR_H
#define GAMEMAPGENERATOR_H

#include "../CourseLib/core/worldgenerator.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "grasstile.h"

namespace Game{

class GameMapGenerator{
public:
    GameMapGenerator();
    ~GameMapGenerator();
    void createMapObjects(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler);


private:
    std::vector<std::vector<int>> mapTemplate;
};
}

#endif // GAMEMAPGENERATOR_H
