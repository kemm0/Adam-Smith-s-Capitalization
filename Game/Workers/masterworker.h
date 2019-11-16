#ifndef MASTERWORKER_H
#define MASTERWORKER_H


#include "../CourseLib/tiles/grassland.h"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/workers/workerbase.h"
#include "../CourseLib/core/resourcemaps.h"

namespace Game {

class MasterWorker: public Course::WorkerBase
{
public:
    MasterWorker(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Course::ConstResourceMaps::BW_WORKER_EFFICIENCY
                );
};
}

#endif // MASTERWORKER_H
