#include "player.h"
#include "gameeventhandler.h"
#include "gameobjectmanager.h"
#include "gamebuildingbase.h"
#include "gametilebase.h"
#include <iostream>
namespace Game{

Player::Player(const Course::Coordinate &coord,
               const std::string &name,
               std::shared_ptr<Game::GameEventHandler> handler,
               std::shared_ptr<Game::GameObjectManager> manager,
               const std::vector<std::shared_ptr<Course::GameObject> > objects,
               QObject *parent)
    : QObject(parent), Course::PlayerBase(name,objects), Course::GameObject(coord,handler,manager)
{
    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png");
    money = 500;
    resources = ConstGameResourceMap::PLAYER_STARTING_RESOURCES;
    emit currentMoney(resources.at(Course::MONEY));
}

Player::~Player()
{

}

QPixmap Player::getSprite()
{
    return sprite;
}

Course::ResourceMap Player::getResources()
{
    return resources;
}

void Player::modifyResources(Course::ResourceMap rmap)
{
    resources = Course::mergeResourceMaps(resources,rmap);
    emit currentMoney(resources.at(Course::MONEY));
}

void Player::getProfit()
{
    for(std::shared_ptr<Course::GameObject> object:getObjects()){
        std::shared_ptr<GameTileBase> tile = std::dynamic_pointer_cast<GameTileBase>(object);
        if(tile){
            tile->generateResources();
        }
    }
}
}
