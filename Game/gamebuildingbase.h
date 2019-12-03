#ifndef GAMEBUILDINGBASE_H
#define GAMEBUILDINGBASE_H

#include "../CourseLib/buildings/buildingbase.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gameresourcemap.h"

namespace Game {

/**
 * @brief The GameBuildingBase class is a base class for buildings with a sprite/image component. Inherited from BuildingBase.
 *
 */
class GameBuildingBase : public Course::BuildingBase


{
public:
    GameBuildingBase(const std::shared_ptr<GameEventHandler>& eventhandler,
                     const std::shared_ptr<GameObjectManager>& objectmanager,
                     const std::shared_ptr<Player>& owner,
                     const int& tilespaces = 1,
                     const Course::ResourceMap& buildcost = {},
                     const Course::ResourceMap& production = {});
    /**
     * @brief getSprite QPixMap graphics for buildings
     * @return returns the sprite
     */
    virtual QPixmap getSprite();
    /**
     * @brief getWidth
     * @return the width of the sprite image
     */
    int getWidth();
    /**
     * @brief getHeight
     * @return the height of the sprite image
     */
    int getHeight();


private:

protected:
    QPixmap sprite;
    int width;
    int height;
};
}

#endif // GAMEBUILDINGBASE_H
