#include "player.h"
#include "gameeventhandler.h"
#include "gameobjectmanager.h"
#include "gamebuildingbase.h"
#include <iostream>
namespace Game{

Player::Player(const Course::Coordinate &coord,
               const std::string &name,
               std::shared_ptr<Game::GameEventHandler> handler,
               std::shared_ptr<Game::GameObjectManager> manager,
               const std::vector<std::shared_ptr<Course::GameObject> > objects)
    : Course::PlayerBase(name,objects), Course::GameObject(coord,handler,manager)
{
    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png");
    startingMoney = 500;
    money = startingMoney;
}

Player::~Player()
{

}

QPixmap Player::getSprite()
{
    return sprite;
    std::shared_ptr<GameBuildingBase> building = std::static_pointer_cast<GameBuildingBase>(getObjects().at(0));
    building->getProduction();
}

int Player::getMoney()
{
    /*if(getObjects().size() != 0){
        std::vector<std::shared_ptr<Course::GameObject>> object = getObjects();
        for(int i=0; i < object.size(); i++){
            std::shared_ptr<GameBuildingBase> building = std::static_pointer_cast<GameBuildingBase>(object.at(i));
            if(building != nullptr){
                std::cout<<getObjects().size()<<std::endl;
                std::cout<<building->holdCount()<<std::endl;
                Course::ResourceMap map = building->getProduction();
                money += map[Course::MONEY];
            }
        }
    }*/
    return money;
}

void Player::setMoney(std::map<Course::BasicResource, int> amount)
{
    money += amount[Course::MONEY];
}

int Player::getStartingMoney()
{
    return startingMoney;
}
}
