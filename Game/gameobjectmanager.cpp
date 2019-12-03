#include <iostream>
#include "gameobjectmanager.h"
#include "gametilebase.h"
#include "Buildings/farmbuilding.h"
#include "Buildings/fishingbuilding.h"
#include "Buildings/loggingbuilding.h"

namespace Game{
GameObjectManager::GameObjectManager(QObject *parent)
    :QObject(parent)
{
    gameObjects_ = {};
    gameTiles = {};
    player_ = nullptr;
    buildings = {};
    workers = {};
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    for(auto tile: tiles){
        if(tile != nullptr){
            gameObjects_.push_back(tile);
        }
    }
}

void GameObjectManager::addGameTile(std::shared_ptr<Game::GameTileBase> tile)
{
    gameTiles.push_back(tile);
}

std::shared_ptr<Course::TileBase> GameObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for(auto tile: gameTiles){
        if(tile->getCoordinate() == coordinate){
            return tile;
        }
    }
    throw "Tile not found";
}



std::shared_ptr<Game::GameTileBase> GameObjectManager::getGameTile(const Course::Coordinate &coordinate)
{
    //std::cout<<"Values i got x: " + std::to_string(coordinate.x()) + " y: "+ std::to_string(coordinate.y())<<std::endl;
    for(std::shared_ptr<Game::GameTileBase> tile: gameTiles){
        if(tile->getCoordinate() == coordinate){
            //std::cout<<"exact same tile found! x: " + std::to_string(tile->getCoordinate().x()) + " y: " + std::to_string(tile->getCoordinate().y())<<std::endl;
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
    for(auto tile: gameTiles){
        if(tile->ID == id){
            return tile;
        }
    }
    throw "ID not found";
}

std::vector<std::shared_ptr<Course::TileBase> > GameObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> foundtiles = {};
    for(auto coordinate: coordinates){
        for(auto tile:gameTiles){
            if(tile->getCoordinate() == coordinate){
                foundtiles.push_back(tile);
            }
        }
    }
    if(foundtiles.size() != 0){
        return foundtiles;
    }
    else{
        throw "no tiles found";
    }
}

std::vector<std::shared_ptr<GameTileBase> > GameObjectManager::getGameTiles()
{
    return gameTiles;

}

void GameObjectManager::setPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

std::shared_ptr<Player> GameObjectManager::getPlayer()
{
    return player_;
}

std::vector<std::shared_ptr<Course::WorkerBase> > GameObjectManager::getWorkers()
{
    return workers;
}

void GameObjectManager::addWorker(std::shared_ptr<Course::WorkerBase> worker)
{
    workers.push_back(worker);
}

void GameObjectManager::addGameObject(std::shared_ptr<Course::GameObject> object)
{
    gameObjects_.push_back(object);
}

void GameObjectManager::addBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    buildings.push_back(building);
}

std::vector<std::shared_ptr<Course::BuildingBase> > GameObjectManager::getBuildings()
{
    return buildings;
}
}
