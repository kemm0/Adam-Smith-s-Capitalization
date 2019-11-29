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
    buildings = {};
    workers = {};
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
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
    throw "tile not found";
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
            std::cout<<"tile found by ID"<<std::endl;
            return tile;
        }
    }
    throw "ID not found";
}

std::vector<std::shared_ptr<Course::TileBase> > GameObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> foundTiles = {};
    for(int i = 0; i< coordinates.size();i++){
        for(auto tile: gameTiles){
            if(tile->getCoordinate() == coordinates.at(i)){
                foundTiles.push_back(tile);
            }
        }
    }
    return foundTiles;
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
