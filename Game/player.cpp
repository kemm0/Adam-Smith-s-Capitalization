#include "player.h"
namespace Game{

Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects)
    : Course::PlayerBase(name,objects)
{
    sprite = new QGraphicsPixmapItem(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/adamsmith.png"));
}

Player::~Player()
{

}
}
