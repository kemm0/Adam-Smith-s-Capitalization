#include "player.h"
#include "gameeventhandler.h"
#include "gameobjectmanager.h"
#include "gamebuildingbase.h"
namespace Game{

Player::Player(const Course::Coordinate &coord,
               const std::string &name,
               std::shared_ptr<Game::GameEventHandler> handler,
               std::shared_ptr<Game::GameObjectManager> manager,
               const std::vector<std::shared_ptr<Course::GameObject> > objects)
    : Course::PlayerBase(name,objects), Course::GameObject(coord,handler,manager)
{
    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png");
    money = 500;
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
    if(getObjects().size() != 0){
        std::vector<std::shared_ptr<Course::GameObject>> object = getObjects();
        for(int i=0; i < object.size(); i++){
            std::shared_ptr<GameBuildingBase> building = std::static_pointer_cast<GameBuildingBase>(object.at(i));
            Course::ResourceMap map = building->getProduction();
            money += map[Course::MONEY];
        }
    }
    return money;
}

bool Player::setMoney(std::map<Course::BasicResource, int> amount)
{
    money += amount[Course::MONEY];
    if (money <= 0){
        return false;
    }
    else{
        return true;
    }
}
}
