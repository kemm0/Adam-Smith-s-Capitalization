#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H


#include "../CourseLib/interfaces/iobjectmanager.h"
#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/core/coordinate.h"
#include "player.h"
#include "../CourseLib/core/worldgenerator.h"
//#include "gameeventhandler.h"

namespace Game{

class GameTileBase;
class FarmBuilding;
class FishingBuilding;
class LoggingBuilding;


class GameObjectManager: public QObject, public Course::iObjectManager
{
Q_OBJECT
public:
    GameObjectManager(QObject *parent = nullptr);
    ~GameObjectManager();
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);
    void addGameTile(std::shared_ptr<Game::GameTileBase> tile);

    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);
    std::vector<std::shared_ptr<Course::GameObject>> getGameObjects();

    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);
    std::vector<std::shared_ptr<Game::GameTileBase>> getGameTiles();
    std::shared_ptr<Game::GameTileBase> getGameTile(const Course::Coordinate& coordinate);
    void loadFromMap();
    void setPlayer(std::shared_ptr<Game::Player> player);
    std::shared_ptr<Game::Player> getPlayer();

private:
    std::vector<std::shared_ptr<Course::GameObject>> gameObjects_;
    std::vector<std::shared_ptr<Game::GameTileBase>> gameTiles;
    std::shared_ptr<Game::Player> player_;
    //Player* player1;
};

}

#endif // GAMEOBJECTMANAGER_H
