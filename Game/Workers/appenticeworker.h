#ifndef APPENTICEWORKER_H
#define APPENTICEWORKER_H


#include "../CourseLib/tiles/grassland.h"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/workers/workerbase.h"
#include "gameresourcemap.h"

namespace Game {

class ApprenticeWorker: public Course::WorkerBase
{
public:
    ApprenticeWorker(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Course::ConstGameResourceMap::AW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Course::ConstGameResourceMap::AW_WORKER_EFFICIENCY
                );
};
}

#endif // APPENTICEWORKER_H
