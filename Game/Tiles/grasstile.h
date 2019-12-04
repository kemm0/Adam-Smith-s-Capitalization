#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "gametilebase.h"
#include "QGraphicsPixmapItem"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
namespace Game{
/**
 * @brief The GrassTile class represents grass
 */
class GrassTile : public Game::GameTileBase//, public QGraphicsPixmapItem
{
public:
    /**
     * @brief GrassTile
     * @param location
     * @param eventhandler
     * @param objectmanager
     * @param max_build
     * @param max_work
     * @param production
     */
    GrassTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    /**
     * @brief getType
     * @return type of the tile as a string
     */
    virtual std::string getType() const override;
private:
};
}

#endif // GRASSTILE_H
