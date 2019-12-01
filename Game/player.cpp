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
}

int Player::getMoney()
{
    for(std::shared_ptr<Course::GameObject> object:getObjects()){
        std::shared_ptr<GameTileBase> tile = std::dynamic_pointer_cast<GameTileBase>(object);
        if(tile){
            std::cout<<"object muutettu tileksi"<<std::endl;
            std::cout<<tile->getType()<<std::endl;
            std::cout<<tile->getBuildingCount()<<std::endl;
            std::cout<<tile->getWorkerCount()<<std::endl;
            tile->generateResources();
        }
        else{
            std::cout<<"Lol ei pysty muuttaan objectia gametileksi"<<std::endl;
        }
    }

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
