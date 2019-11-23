#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "gametilebase.h"
#include "QGraphicsPixmapItem"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
namespace Game{

class GrassTile : public Game::GameTileBase//, public QGraphicsPixmapItem
{
public:
    GrassTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
              virtual std::string getType() const override;
    virtual QGraphicsPixmapItem* getSprite() override;
private:
    QGraphicsPixmapItem* sprite;
};
}

#endif // GRASSTILE_H
