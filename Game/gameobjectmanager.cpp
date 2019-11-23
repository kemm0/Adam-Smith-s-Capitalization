#include "gameobjectmanager.h"
#include "gametilebase.h"

namespace Game{
GameObjectManager::GameObjectManager(){
    size = 0;
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{

}

void GameObjectManager::addTile(std::shared_ptr<Game::GameTileBase> tile)
{
    gameTiles.push_back(tile);
}

void GameObjectManager::addBuilding(std::shared_ptr<Course::BuildingBase> building , std::shared_ptr<Game::Player> player)
{
    gameObjects_.push_back(building);
    player->addObject(building);
}

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::Coordinate &coordinate)
{

}

std::vector<std::shared_ptr<Course::GameObject> > GameObjectManager::getGameObjects()
{
    return gameObjects_;
}

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::ObjectId &id)
{

}

std::vector<std::shared_ptr<Course::TileBase> > GameObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{

}

std::vector<std::shared_ptr<GameTileBase> > GameObjectManager::getGameTiles()
{
    return gameTiles;

}

void GameObjectManager::loadFromMap()
{
}

void GameObjectManager::initMap(std::shared_ptr<Game::GameEventHandler> handler)
{
}

void GameObjectManager::setPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

std::shared_ptr<Player> GameObjectManager::getPlayer()
{
    return player_;
}
}
