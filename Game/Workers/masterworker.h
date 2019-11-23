#ifndef MASTERWORKER_H
#define MASTERWORKER_H


#include "../CourseLib/tiles/grassland.h"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/workers/workerbase.h"
#include "gameresourcemap.h"

namespace Game {

class MasterWorker: public Course::WorkerBase
{
public:
    MasterWorker(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Game::ConstGameResourceMap::MW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Game::ConstGameResourceMap::MW_WORKER_EFFICIENCY
                );
};
}

#endif // MASTERWORKER_H
