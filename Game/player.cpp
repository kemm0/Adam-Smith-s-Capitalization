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
}
