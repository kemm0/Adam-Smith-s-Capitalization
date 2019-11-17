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

void GameObjectManager::addTile(std::shared_ptr<Course::TileBase> tile)
{
 gameObjects_.push_back(tile);
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
