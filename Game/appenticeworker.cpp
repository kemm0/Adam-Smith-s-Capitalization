#include "appenticeworker.h"
namespace Game {


ApprenticeWorker::ApprenticeWorker(const std::shared_ptr<GameEventHandler>& eventhandler,
                         const std::shared_ptr<GameObjectManager>& objectmanager,
                         const std::shared_ptr<Player>& owner,
                         const int& tilespaces,
                         const Course::ResourceMap& cost,
                         const Course::ResourceMapDouble& efficiency):
    Course::WorkerBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        cost,
        efficiency)
{

}
}
