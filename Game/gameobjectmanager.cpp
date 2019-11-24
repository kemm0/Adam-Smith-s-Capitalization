#include <iostream>
#include "gameobjectmanager.h"
#include "gametilebase.h"
#include "Buildings/farmbuilding.h"
#include "Buildings/fishingbuilding.h"
#include "Buildings/loggingbuilding.h"

namespace Game{
GameObjectManager::GameObjectManager(){
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

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::Coordinate &coordinate)
{

}



std::shared_ptr<Game::GameTileBase> GameObjectManager::getGameTile(const Course::Coordinate &coordinate)
{
    for(std::shared_ptr<Game::GameTileBase> tile: gameTiles){

        int targetTilex = tile->getCoordinate().x();
        int targetTiley = tile->getCoordinate().y();
        bool isWithingTileX = (coordinate.x() >= targetTilex && coordinate.x() <= (targetTilex + tile->getWidth()));
        bool isWithinTileY = (coordinate.y() >= targetTiley && coordinate.y() <= (targetTiley + tile->getHeight()));

        if(isWithingTileX && isWithinTileY){
            std::cout<<"asd"<<std::endl;
            return tile;
        }
    }
    return nullptr;
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

void GameObjectManager::setPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

std::shared_ptr<Player> GameObjectManager::getPlayer()
{
    return player_;
}
}
