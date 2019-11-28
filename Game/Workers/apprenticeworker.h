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
                    Game::ConstGameResourceMap::AW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Game::ConstGameResourceMap::AW_WORKER_EFFICIENCY
                );
    virtual std::string getType() const override;
    virtual void doSpecialAction();
};
}

#endif // APPENTICEWORKER_H
