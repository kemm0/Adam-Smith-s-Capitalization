#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"
#include "QGraphicsPixmapItem"
namespace Game{
class GameEventHandler;
class GameObjectManager;

class Player : public Course::PlayerBase, public Course::GameObject
{
public:
    Player(const Course::Coordinate &coord,
           const std::string& name = "Adam Smith",
           std::shared_ptr<Game::GameEventHandler> handler = nullptr,
           std::shared_ptr<Game::GameObjectManager> manager = nullptr,
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {});
    ~Player();
    QPixmap getSprite();

private:
        QPixmap sprite;

};
}

#endif // PLAYER_H
