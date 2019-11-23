#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H


#include "../CourseLib/interfaces/iobjectmanager.h"
#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/core/coordinate.h"
#include "player.h"
#include "../CourseLib/core/worldgenerator.h"
#include "gameeventhandler.h"

namespace Game{

class GameTileBase;

class GameObjectManager: public Course::iObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);
    void addTile(std::shared_ptr<Game::GameTileBase> tile);
    void addBuilding(std::shared_ptr<Course::BuildingBase> building, std::shared_ptr<Game::Player> player);

    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);
    std::vector<std::shared_ptr<Course::GameObject>> getGameObjects();

    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);
    std::vector<std::shared_ptr<Game::GameTileBase>> getGameTiles();
    void loadFromMap();
    void initMap(std::shared_ptr<GameEventHandler> handler);
    int size;
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
