#ifndef NOVICEWORKER_H
#define NOVICEWORKER_H

#include "../CourseLib/tiles/grassland.h"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/workers/workerbase.h"
#include "gameresourcemap.h"

namespace Game {
/**
 * @brief The NoviceWorker class represents novice worker
 */
class NoviceWorker: public Course::WorkerBase
{
public:
    NoviceWorker(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Game::ConstGameResourceMap::NW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Game::ConstGameResourceMap::NW_WORKER_EFFICIENCY
                );
    virtual std::string getType() const override;
    virtual void doSpecialAction();
};
}
#endif // NOVICEWORKER_H
