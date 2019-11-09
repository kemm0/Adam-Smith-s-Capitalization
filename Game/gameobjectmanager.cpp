#include "gameobjectmanager.h"
GameObjectManager::GameObjectManager(){
    //const std::string& name,    const std::vector<std::shared_ptr<Course::GameObject> > objects
    //player1 = new Player("Adam Smith",{});
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{

}
void GameObjectManager::loadFromMap(std::vector<std::vector<int>>& objectMap){

}

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::Coordinate &coordinate)
{

}

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::ObjectId &id)
{

}

std::vector<std::shared_ptr<Course::TileBase> > GameObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{

}
